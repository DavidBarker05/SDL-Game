#include "Game.h"
#include <SDL2/SDL.h>

Game::Game() : m_GameIsRunning(false), m_GameRenderer(), m_EventManager() { }

Game::~Game()
{
	m_GameRenderer.Destroy();
	SDL_Quit();
}

void Game::Init(const char* title, int width, int height)
{
	m_GameRenderer.Init();
	m_GameRenderer.CreateWindow(title, width, height, 0);
	m_GameRenderer.CreateRenderer(-1, 0);
	m_EventManager.Init();
}

void Game::Run()
{
	m_GameIsRunning = true;
	while (m_GameIsRunning)
	{
		PollStatus status = m_EventManager.PollEvents();
		if (status == PollStatus::QUIT)
		{
			m_GameIsRunning = false;
			return;
		}
		m_GameRenderer.Render();
	}
}
