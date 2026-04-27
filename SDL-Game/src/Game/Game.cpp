#include "Game.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>
#include <memory>
#include "Scene.h"
#include "GameRenderer.h"
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
	if (!GameRenderer::Init()) return false;
	if (!EventManager::Init()) return false;
	spScene = std::make_shared<Scene>();
	return true;
}

void Game::Shutdown()
{
	GameRenderer::Shutdown();
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
	GameRenderer::Render();
}

void Game::UpdateDeltaTime()
{
	m_CurrentFrameTime = SDL_GetPerformanceCounter();
	m_DeltaTime = (m_CurrentFrameTime - m_LastFrameTime) / (FLOAT64) SDL_GetPerformanceFrequency();
	m_LastFrameTime = m_CurrentFrameTime;
}
