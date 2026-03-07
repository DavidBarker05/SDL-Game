#include "Game.h"
#include <SDL2/SDL.h>

Game::Game() : m_bGameIsRunning(FALSE), m_DeltaTime(0.0f), m_GameRenderer(), m_EventManager() { }

Game::~Game()
{
	m_GameRenderer.Destroy();
	SDL_Quit();
}

void Game::Init()
{
	m_GameRenderer.Init();
	m_EventManager.Init();
}

void Game::Run()
{
	m_bGameIsRunning = TRUE;
	static INT64 lastTick = 0i64;
	while (m_bGameIsRunning)
	{
		PollStatus status = m_EventManager.PollEvents();
		if (status == PollStatus::eQUIT)
		{
			m_bGameIsRunning = FALSE;
			return;
		}
		m_GameRenderer.Render();
		INT64 currentTick = SDL_GetTicks64();
		m_DeltaTime = (currentTick - lastTick) / 1000.0f;
		lastTick = currentTick;
	}
}

const GameRenderer& Game::GetGameRenderer() { return m_GameRenderer; }

const EventManager& Game::GetEventManager() { return m_EventManager; }
