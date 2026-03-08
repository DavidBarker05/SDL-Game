#include "Game.h"
#include <SDL2/SDL.h>
#include "Player.h"
#include "Scene.h"

Game::Game() : m_bGameIsRunning(FALSE), m_CurrentFrameTime(0.0), m_LastFrameTime(0.0), m_DeltaTime(0.0), m_FixedTickRate(0.02), m_FixedDeltaTime(0.0), m_GameRenderer(), m_EventManager() { }

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
	SDL_Delay(200); // Delay the window for a few milliseconds so that it appears on top of vs console
#endif // _DELAY_WINDOW
	Logger::Init();
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

void Game::Tick()
{
	// Movement gets very weird when running full speed rn (7000fps) and drops to like 6000fps
	m_CurrentFrameTime = SDL_GetPerformanceCounter();
	m_DeltaTime = (m_CurrentFrameTime - m_LastFrameTime) / (FLOAT64) SDL_GetPerformanceFrequency();
	if (m_DeltaTime > 0.25) m_DeltaTime = 0.25;
	m_FixedDeltaTime += m_DeltaTime;
	PollStatus status = m_EventManager.PollEvents();
	if (status == PollStatus::eQUIT)
	{
		m_bGameIsRunning = FALSE;
		return;
	}
	while (m_FixedDeltaTime >= m_FixedTickRate)
	{
		pScene->TickPhysics(m_FixedTickRate);
		m_FixedDeltaTime -= m_FixedTickRate;
	}
	pScene->Tick(m_DeltaTime);
	m_GameRenderer.Render();
	m_LastFrameTime = m_CurrentFrameTime;
	SDL_Delay(1); // Delay by 1 for now so that the frame drops aren't as bad
}
