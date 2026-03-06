#include "GameRenderer.h"
#include <SDL2/SDL.h>

void GameRenderer::Init()
{
	SDL_Init(SDL_INIT_VIDEO);
}

void GameRenderer::Destroy()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
}

void GameRenderer::CreateWindow(CSTRING title, INT16 width, INT16 height, UINT32 flags)
{
	m_pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
}

void GameRenderer::CreateRenderer(INT16 index, UINT32 flags)
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
