#include "GameRenderer.h"
#include <SDL2/SDL.h>
#include "Scene.h"

#define DEFAULT_WINDOW_TITLE  "Title"
#define DEFAULT_WINDOW_WIDTH  640
#define DEFAULT_WINDOW_HEIGHT 480

#define DEFAULT_RENDERER_INDEX -1

bool GameRenderer::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO)) return FALSE;
	m_pWindow = SDL_CreateWindow(DEFAULT_WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	m_pRenderer = SDL_CreateRenderer(m_pWindow, DEFAULT_RENDERER_INDEX, SDL_RENDERER_ACCELERATED);
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
