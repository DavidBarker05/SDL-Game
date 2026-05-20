#include "Renderer.h"
#include "Logging/Log.h"
#include <algorithm>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <vector>

#define DEFAULT_WINDOW_TITLE "Title"
#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480

static SDL_Window* s_pWindow = nullptr;
static SDL_Renderer* s_pRenderer = nullptr;
static SDL_GPUDevice* s_pGPUDevice = nullptr;

#define RECT_ID 0u
#define FILLED_RECT_ID 1u
#define TEXTURE_ID 2u

struct RenderBufferItem
{
	UINT32 Layer;
	UINT32 ShapeID;
	Vector2 Position;
	Vector2 HalfExtents;
	union
	{
		SIZE_T ColourIndex;
		SIZE_T TextureIndex;
	};
};

static std::vector<RenderBufferItem> s_RenderBuffer;
static std::vector<Color> s_ColourBuffer;

bool Renderer::Init(CSTRING title, UINT32 windowWidth, UINT32 windowHeight)
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		LOG_FATAL("%s", SDL_GetError());
		return false;
	}
	if (!(s_pWindow =
			  SDL_CreateWindow(title, windowWidth, windowHeight, SDL_WINDOW_HIGH_PIXEL_DENSITY)))
	{
		LOG_FATAL("%s", SDL_GetError());
		return false;
	}
	if (!(s_pRenderer = SDL_CreateGPURenderer(nullptr, s_pWindow)))
	{
		LOG_FATAL("%s", SDL_GetError());
		return false;
	}
	s_pGPUDevice = SDL_GetGPURendererDevice(s_pRenderer);
	SDL_SetGPUSwapchainParameters(s_pGPUDevice, s_pWindow, SDL_GPU_SWAPCHAINCOMPOSITION_SDR,
								  SDL_GPU_PRESENTMODE_IMMEDIATE); // Disable vsync
	LOG_INFO("Initialised the game renderer");
	return true;
}

bool Renderer::Init()
{
	return Init(DEFAULT_WINDOW_TITLE, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
}

void Renderer::Shutdown()
{
	SDL_DestroyRenderer(s_pRenderer);
	SDL_DestroyWindow(s_pWindow);
}

void Renderer::DrawRect(UINT32 drawLayer, Vector2 position, Vector2 halfExtents, Color color)
{
	s_ColourBuffer.emplace_back(color);
	SIZE_T colourIndex = s_ColourBuffer.size() - 1;
	s_RenderBuffer.emplace_back(
		RenderBufferItem {drawLayer, RECT_ID, position, halfExtents, colourIndex});
}

void Renderer::DrawFilledRect(UINT32 drawLayer, Vector2 position, Vector2 halfExtents, Color color)
{
	s_ColourBuffer.emplace_back(color);
	SIZE_T colourIndex = s_ColourBuffer.size() - 1;
	s_RenderBuffer.emplace_back(
		RenderBufferItem {drawLayer, FILLED_RECT_ID, position, halfExtents, colourIndex});
}

static void SortRenderBuffer()
{
	std::sort(s_RenderBuffer.begin(), s_RenderBuffer.end(),
			  [](const RenderBufferItem& left, const RenderBufferItem& right) -> bool
			  { return left.Layer < right.Layer; });
}

static void DoRect(Vector2 position, Vector2 halfExtents, Color colour)
{
	SDL_FRect r = {position.x - halfExtents.x, position.y - halfExtents.y, halfExtents.x * 2.0f,
				   halfExtents.y * 2.0f};
	SDL_SetRenderDrawColor(s_pRenderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderRect(s_pRenderer, &r);
}

static void DoFilledRect(Vector2 position, Vector2 halfExtents, Color colour)
{
	SDL_FRect r = {position.x - halfExtents.x, position.y - halfExtents.y, halfExtents.x * 2.0f,
				   halfExtents.y * 2.0f};
	SDL_SetRenderDrawColor(s_pRenderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderFillRect(s_pRenderer, &r);
}

void Renderer::Render()
{
	SDL_SetRenderDrawColor(s_pRenderer, 0, 0, 0, 255); // Flush the screen with black background
	SDL_RenderClear(s_pRenderer);
	SortRenderBuffer();
	// Render everything below here
	for (RenderBufferItem item : s_RenderBuffer)
	{
		switch (item.ShapeID)
		{
			case RECT_ID:
				DoRect(item.Position, item.HalfExtents, s_ColourBuffer.at(item.ColourIndex));
				break;
			case FILLED_RECT_ID:
				DoFilledRect(item.Position, item.HalfExtents, s_ColourBuffer.at(item.ColourIndex));
				break;
			case TEXTURE_ID:
				break;
			default:
				LOG_ERROR("%u is not a valid ShapeID", item.ShapeID);
				break;
		}
	}
	// Render everything above here
	s_RenderBuffer.clear();
	s_ColourBuffer.clear();
	SDL_RenderPresent(s_pRenderer);
}
