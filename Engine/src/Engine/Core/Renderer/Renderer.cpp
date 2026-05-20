#include "Renderer.h"
#include "Logging/Log.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>

#define DEFAULT_WINDOW_TITLE "Title"
#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480

static SDL_Window* s_pWindow = nullptr;
static SDL_Renderer* s_pRenderer = nullptr;
static SDL_GPUDevice* s_pGPUDevice = nullptr;

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

void Renderer::Render()
{
	SDL_SetRenderDrawColor(s_pRenderer, 0, 0, 0, 255); // Flush the screen with black background
	SDL_RenderClear(s_pRenderer);
	// Render everything below here
	// Render everything above here
	SDL_RenderPresent(s_pRenderer);
}
