#include "Game.h"
#include "GameRenderer.h"
#include "EventManager.h"
#include <SDL2/SDL.h>
#include "Player.h"

Game::Game() : m_bGameIsRunning(FALSE), m_DeltaTime(0.0f), m_upGameRenderer(std::make_unique<GameRenderer>()), m_upEventManager(std::make_unique<EventManager>()) { }

Game::~Game()
{
	m_upGameRenderer->Destroy();
	SDL_Quit();
}

Player* player;

void Game::Init()
{
	m_upGameRenderer->Init();
	m_upEventManager->Init();
	player = new Player(this);
}


void Game::Start()
{
	m_bGameIsRunning = TRUE;
	player->Start();
	while (m_bGameIsRunning) Tick();
}

GameRenderer* Game::GetGameRenderer() { return m_upGameRenderer.get(); }

EventManager* Game::GetEventManager() { return m_upEventManager.get(); }

void Game::Tick()
{
	UpdateDeltaTime();
	PollStatus status = m_upEventManager->PollEvents();
	if (status == PollStatus::eQUIT)
	{
		m_bGameIsRunning = FALSE;
		return;
	}
	player->Tick(m_DeltaTime);
	m_upGameRenderer->Render();
}

void Game::UpdateDeltaTime()
{
	static UINT64 lastTick = 0i64;
	UINT64 currentTick = SDL_GetPerformanceCounter();
	m_DeltaTime = (currentTick - lastTick) / (FLOAT64) SDL_GetPerformanceFrequency();
	lastTick = currentTick;
}
