#include "Game.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>
#include "Player.h"
#include "Scene.h"
#include "EventManager.h"

#ifdef _MSC_VER
#pragma warning(disable: 4244)
#endif // _MSC_VER

std::shared_ptr<Scene> spScene;

bool Game::Init()
{
#ifdef _DELAY_WINDOW
	SDL_Delay(200); // Delay the window for a few milliseconds so that it appears on top of vs console
#endif // _DELAY_WINDOW
#define TEST
	Logger::Init();
	if (!m_GameRenderer.Init()) return false;
	if (!EventManager::Init()) return false;
	spScene = std::make_shared<Scene>();
	m_GameRenderer.AddRenderable((std::weak_ptr<Renderable>) spScene);
	return true;
}

void Game::Shutdown()
{
	m_GameRenderer.Destroy();
	EventManager::Shutdown();
	SDL_Quit();
}

void Game::Start()
{
	m_bGameIsRunning = true;
	while (m_bGameIsRunning) Tick();
}

void Game::Tick()
{
	UpdateDeltaTime();
	UINT32 status = EventManager::PollEvents();
	if (status == EventManager::Quit)
	{
		m_bGameIsRunning = false;
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
