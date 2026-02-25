#include "Game.h"
#include <SDL.h>

#define SDL_INIT_FLAGS SDL_INIT_VIDEO | SDL_INIT_EVENTS

Game::Game(const char* title, int width, int height)
{
	SDL_Init(SDL_INIT_FLAGS);
	m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	m_Renderer = SDL_CreateRenderer(m_Window, -1, 0);
	m_GameIsRunning = false;
}

Game::~Game()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void Game::Run()
{
	m_GameIsRunning = true;
	SDL_Event event;
	while (m_GameIsRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				m_GameIsRunning = false;
				return;
			}
			m_InputManager.ProcessEvent(event);
		}
		RenderGame();
	}
}

void Game::RenderGame()
{
	SDL_RenderClear(m_Renderer);
	// Render everything below here
	
	// Render everything above here
	SDL_RenderPresent(m_Renderer);
}
