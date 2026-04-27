#include "Game.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_timer.h>
#include <memory>
#include "Scene.h"
#include "Renderer/Renderer.h"
#include "Events/EventSystem.h"

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
	if (!Renderer::Init()) return false;
	if (!EventSystem::Init()) return false;
	spScene = std::make_shared<Scene>();
	return true;
}

void Game::Shutdown()
{
	Renderer::Shutdown();
	EventSystem::Shutdown();
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
	UINT32 status = EventSystem::PollEvents();
	if (status == EventSystem::Quit)
	{
		m_bGameIsRunning = false;
		return;
	}
	spScene->Tick(m_DeltaTime);
	Renderer::Render();
}

void Game::UpdateDeltaTime()
{
	m_CurrentFrameTime = SDL_GetPerformanceCounter();
	m_DeltaTime = (m_CurrentFrameTime - m_LastFrameTime) / (FLOAT64) SDL_GetPerformanceFrequency();
	m_LastFrameTime = m_CurrentFrameTime;
}
