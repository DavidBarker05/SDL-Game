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
	if (m_pScene) m_pScene->Render(m_pRenderer);
	// Render everything above here
	SDL_RenderPresent(m_pRenderer);
}

void GameRenderer::SetScene(Scene* pScene)
{
	m_pScene = pScene;
}
