#include "GameRenderer.h"
#include <SDL2/SDL.h>
#include "Player.h"

#define DEFAULT_WINDOW_TITLE  "Title"
#define DEFAULT_WINDOW_WIDTH  640
#define DEFAULT_WINDOW_HEIGHT 480
#define DEFAULT_WINDOW_FLAGS  0

#define DEFAULT_RENDERER_INDEX -1
#define DEFAULT_RENDERER_FLAGS 0

void GameRenderer::Init()
{
	SDL_Init(SDL_INIT_VIDEO);
	m_pWindow = SDL_CreateWindow(DEFAULT_WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_FLAGS);
	m_pRenderer = SDL_CreateRenderer(m_pWindow, DEFAULT_RENDERER_INDEX, DEFAULT_RENDERER_FLAGS);
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
	
	if (m_pPlayer)
	{
		m_pPlayer->Render(m_pRenderer);
		m_pPlayer = NULL;
	}

	// Render everything above here
	SDL_RenderPresent(m_pRenderer);
}

void GameRenderer::SetPlayer(Player* pPlayer)
{
	m_pPlayer = pPlayer;
}
