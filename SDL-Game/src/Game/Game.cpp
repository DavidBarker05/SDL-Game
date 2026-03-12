#include "Game.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>
#include "Player.h"
#include "Scene.h"

#ifdef _MSC_VER
#pragma warning(disable: 4244)
#endif // _MSC_VER

Game::Game() : m_bGameIsRunning(FALSE), m_CurrentFrameTime(0), m_LastFrameTime(0), m_DeltaTime(0.0), m_GameRenderer(), m_EventManager() { }

Game::~Game()
{
	m_GameRenderer.Destroy();
	SDL_Quit();
}

//Scene* pScene;
Player* pPlayer;

std::shared_ptr<Scene> spScene;

bool Game::Init()
{
#ifdef _DELAY_WINDOW
	SDL_Delay(200); // Delay the window for a few milliseconds so that it appears on top of vs console
#endif // _DELAY_WINDOW
#define TEST
	Logger::Init();
	if (!m_GameRenderer.Init())
	{
		LOG_FATAL("Failed to initialise the game renderer");
		return false;
	}
	if (!m_EventManager.Init())
	{
		LOG_FATAL("Failed to initialise the event system");
		return false;
	}
	spScene = std::make_shared<Scene>();
	//pScene = new Scene();
	pPlayer = new Player();
	//pScene->AddEntity(pPlayer);
	m_EventManager.SetScene(spScene.get());
	spScene->AddEntity(pPlayer);
	m_GameRenderer.AddRenderable((std::weak_ptr<Renderable>) spScene);
	return true;
}


void Game::Start()
{
	m_bGameIsRunning = TRUE;
	while (m_bGameIsRunning) Tick();
}

void Game::Tick()
{
	UpdateDeltaTime();
	PollStatus status = m_EventManager.PollEvents();
	if (status == PollStatus::eQUIT)
	{
		m_bGameIsRunning = FALSE;
		return;
	}
	spScene->Tick(m_DeltaTime);
	m_GameRenderer.Render();
}

void Game::UpdateDeltaTime()
{
	// Movement gets very weird when running full speed rn (7000fps) and drops to like 6000fps
	m_CurrentFrameTime = SDL_GetPerformanceCounter();
	m_DeltaTime = (m_CurrentFrameTime - m_LastFrameTime) / (FLOAT64) SDL_GetPerformanceFrequency();
	m_LastFrameTime = m_CurrentFrameTime;
}
