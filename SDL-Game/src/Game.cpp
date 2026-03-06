#include "Game.h"
#include <SDL2/SDL.h>

Game::Game() : m_bGameIsRunning(FALSE), m_DeltaTime(0.0), m_GameRenderer(), m_EventManager() { }

Game::~Game()
{
	m_GameRenderer.Destroy();
	SDL_Quit();
}

void Game::Init(CSTRING title, INT16 width, INT16 height)
{
	m_GameRenderer.Init();
	m_GameRenderer.CreateWindow(title, width, height, 0);
	m_GameRenderer.CreateRenderer(-1, 0);
	m_EventManager.Init();
}

void Game::Run()
{
	m_bGameIsRunning = TRUE;
	while (m_bGameIsRunning)
	{
		PollStatus status = m_EventManager.PollEvents();
		if (status == PollStatus::eQUIT)
		{
			m_bGameIsRunning = FALSE;
			return;
		}
		m_GameRenderer.Render();
	}
}
