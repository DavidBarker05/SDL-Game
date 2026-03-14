#include "GameRenderer.h"
#include <SDL3/SDL_init.h>
#include "Renderable.h"

#define DEFAULT_WINDOW_TITLE  "Title"
#define DEFAULT_WINDOW_WIDTH  640
#define DEFAULT_WINDOW_HEIGHT 480

bool GameRenderer::Init()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		LOG_FATAL("%s", SDL_GetError());
		return false;
	}
	if (!(m_pWindow = SDL_CreateWindow(DEFAULT_WINDOW_TITLE, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_HIGH_PIXEL_DENSITY)))
	{
		LOG_FATAL("%s", SDL_GetError());
		return false;
	}
	if (!(m_pRenderer = SDL_CreateGPURenderer(nullptr, m_pWindow)))
	{
		LOG_FATAL("%s", SDL_GetError());
		return false;
	}
	m_pGPUDevice = SDL_GetGPURendererDevice(m_pRenderer);
	SDL_SetGPUSwapchainParameters(m_pGPUDevice, m_pWindow, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_IMMEDIATE); // Disable vsync
	LOG_INFO("Initialised the game renderer");
	return true;
}

void GameRenderer::Destroy()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
}

void GameRenderer::Render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255); // Flush the screen with black background
	SDL_RenderClear(m_pRenderer);
	// Render everything below here
	std::vector<std::weak_ptr<Renderable>>::iterator it = m_wpRenderables.begin();
	while (it != m_wpRenderables.end())
	{
		if (std::shared_ptr<Renderable> spRenderable = (*it).lock()) // It hasn't expired
		{
			spRenderable->Render(*this);
			++it;
		}
		else it = m_wpRenderables.erase(it); // It has expired so we shouldn't render it anymore
	}
	// Render everything above here
	SDL_RenderPresent(m_pRenderer);
}

bool GameRenderer::DoesVectorContainRenderable(std::weak_ptr<Renderable> wpRenderable)
{
	return std::find_if(m_wpRenderables.begin(), m_wpRenderables.end(), [wpRenderable](std::weak_ptr<Renderable> wpVectorElement) { return wpRenderable.owner_before(wpVectorElement); }) != m_wpRenderables.end();
}

void GameRenderer::AddRenderable(std::weak_ptr<Renderable> wpRenderable)
{
	if (!DoesVectorContainRenderable(wpRenderable)) m_wpRenderables.emplace_back(wpRenderable);
	else LOG_ERROR("Renderable is already in the renderable vector");
}

void GameRenderer::AddRenderableAtIndex(std::weak_ptr<Renderable> wpRenderable, SIZE_T index)
{
	std::vector<std::weak_ptr<Renderable>>::iterator emplacePosition = m_wpRenderables.begin() + index;
	if (m_wpRenderables.begin() > emplacePosition || m_wpRenderables.end() <= emplacePosition)
	{
		LOG_ERROR("Index %llu is out of bounds of the renderable vector", index);
		return;
	}
	if (!DoesVectorContainRenderable(wpRenderable)) m_wpRenderables.emplace(emplacePosition, wpRenderable);
	else LOG_ERROR("Renderable is already in the renderable vector");
}

void GameRenderer::RemoveRenderable(std::weak_ptr<Renderable> wpRenderable)
{
	// Yes this line is just to remove one element fml, it does remove all instances of an element tho just in case
	m_wpRenderables.erase(std::remove_if(m_wpRenderables.begin(), m_wpRenderables.end(), [wpRenderable](std::weak_ptr<Renderable> wpVectorElement) { return wpRenderable.owner_before(wpVectorElement); }), m_wpRenderables.end());
}

void GameRenderer::RenderRectangle(Vec2D center, Vec2D halfExtents, UINT8 red, UINT8 green, UINT8 blue, UINT8 alpha)
{
	SDL_FRect r = { center.x - halfExtents.x, center.y - halfExtents.y, halfExtents.x * 2.0f, halfExtents.y * 2.0f };
	SDL_SetRenderDrawColor(m_pRenderer, red, green, blue, alpha);
	SDL_RenderFillRect(m_pRenderer, &r);
}

void GameRenderer::RenderTexture(SDL_Texture* pTexture, Vec2D center, Vec2D halfExtents)
{
	SDL_FRect r = { center.x - halfExtents.x, center.y - halfExtents.y, halfExtents.x * 2.0f, halfExtents.y * 2.0f };
	SDL_RenderTexture(m_pRenderer, pTexture, nullptr, &r);
}
