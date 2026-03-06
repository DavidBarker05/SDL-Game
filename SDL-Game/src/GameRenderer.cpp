#include "GameRenderer.h"
#include <SDL2/SDL.h>

void GameRenderer::Init()
{
	SDL_Init(SDL_INIT_VIDEO);
}

void GameRenderer::Destroy()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyRenderer(m_pRenderer);
}

void GameRenderer::CreateWindow(const char* title, int width, int height, Uint32 flags)
{
	m_pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
}

void GameRenderer::CreateRenderer(int index, Uint32 flags)
{
	m_pRenderer = SDL_CreateRenderer(m_pWindow, index, flags);
}

void GameRenderer::Render()
{
	SDL_RenderClear(m_pRenderer);
	// Render everything below here

	// Render everything above here
	SDL_RenderPresent(m_pRenderer);
}
