#include "Game.h"
#include "GameRenderer.h"
#include "EventManager.h"
#include <SDL2/SDL.h>
#include "Player.h"

Game::Game() : m_bGameIsRunning(FALSE), m_CurrentFrameTime(0.0f), m_LastFrameTime(0.0f), m_DeltaTime(0.0f), m_GameRenderer(), m_EventManager() { }

Game::~Game()
{
	m_GameRenderer.Destroy();
	SDL_Quit();
}

Player* player;

void Game::Init()
{
	m_GameRenderer.Init();
	m_EventManager.Init();
	player = new Player(this);
}


void Game::Start()
{
	m_bGameIsRunning = TRUE;
	player->Start();
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
	player->Tick(m_DeltaTime);
	m_GameRenderer.Render();
	m_LastFrameTime = m_CurrentFrameTime;
}
