#include "Game.h"
#include <SDL2/SDL.h>
#include "../Player.h"
#include "Scene.h"

Game::Game() : m_bGameIsRunning(FALSE), m_CurrentFrameTime(0.0f), m_LastFrameTime(0.0f), m_DeltaTime(0.0f), m_GameRenderer(), m_EventManager() { }

Game::~Game()
{
	m_GameRenderer.Destroy();
	SDL_Quit();
}

Scene* pScene;
Player* pPlayer;

bool Game::Init()
{
#ifdef _DELAY_WINDOW
	SDL_Delay(100); // Delay the window for a few milliseconds so that it appears on top of vs console
#endif // _DELAY_WINDOW
	if (!m_GameRenderer.Init())
	{
		// Log error
		return false;
	}
	if (!m_EventManager.Init())
	{
		// Log error
		return false;
	}
	pScene = new Scene();
	pPlayer = new Player();
	pScene->AddEntity(pPlayer);
	m_GameRenderer.SetScene(pScene);
	m_EventManager.SetScene(pScene);
	return true;
}


void Game::Start()
{
	m_bGameIsRunning = TRUE;
	while (m_bGameIsRunning) Tick();
}

GameRenderer& Game::GetGameRenderer()
{
	return m_GameRenderer;
}

EventManager& Game::GetEventManager()
{
	return m_EventManager;
}

void Game::Tick()
{
	// Movement gets very weird when running full speed rn (7000fps) and drops to like 6000fps
	m_CurrentFrameTime = SDL_GetPerformanceCounter();
	m_DeltaTime = (m_CurrentFrameTime - m_LastFrameTime) / (FLOAT32) SDL_GetPerformanceFrequency();
	PollStatus status = m_EventManager.PollEvents();
	if (status == PollStatus::eQUIT)
	{
		m_bGameIsRunning = FALSE;
		return;
	}
	pScene->Tick(m_DeltaTime);
	m_GameRenderer.Render();
	m_LastFrameTime = m_CurrentFrameTime;
}
