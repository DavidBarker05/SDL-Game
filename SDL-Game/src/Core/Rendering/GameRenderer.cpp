#include "GameRenderer.h"
#include <SDL3/SDL_init.h>
#include "Scene.h"

#define DEFAULT_WINDOW_TITLE  "Title"
#define DEFAULT_WINDOW_WIDTH  640
#define DEFAULT_WINDOW_HEIGHT 480


#ifdef _MSC_VER
extern "C"
{
	// Force game to use discrete graphics if they have integrated graphics
	// I might switch to SDL3 since they apparently have an option to fix this we'll see
	//__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
	//__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}
#endif // _MSC_VER


bool GameRenderer::Init()
{
	if (!SDL_Init(SDL_INIT_VIDEO)) return FALSE;
	// Switched to SDL3 should see if laptop uses discrete graphics now or not
	m_pWindow = SDL_CreateWindow(DEFAULT_WINDOW_TITLE, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_HIGH_PIXEL_DENSITY);
	m_pRenderer = SDL_CreateRenderer(m_pWindow, NULL);
	LOG_INFO("Initialised the game renderer");
	return TRUE;
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
			spRenderable->Render(m_pRenderer);
			++it;
		}
		else it = m_wpRenderables.erase(it); // It has expired so we shouldn't render it anymore
	}
	//if (m_pScene) m_pScene->Render(m_pRenderer);
	// Render everything above here
	SDL_RenderPresent(m_pRenderer);
}

bool GameRenderer::DoesVectorContainRenderable(std::weak_ptr<Renderable> wpRenderable)
{
	if (std::find_if(m_wpRenderables.begin(), m_wpRenderables.end(), [wpRenderable](std::weak_ptr<Renderable> wpVectorElement) { return wpRenderable.owner_before(wpVectorElement); }) == m_wpRenderables.end()) return FALSE;
	else return TRUE;
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
