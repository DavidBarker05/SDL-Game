#ifndef GAME_H
#define GAME_H

#include "Core.h"
#include "GameRenderer.h"
#include "EventManager.h"

class Game
{
public:
	Game();
	~Game();

	bool Init();
	void Start();

	GameRenderer& GetGameRenderer();
	EventManager& GetEventManager();

private:
	void Tick();

	bool m_bGameIsRunning;
	FLOAT64 m_CurrentFrameTime;
	FLOAT64 m_LastFrameTime;
	FLOAT64 m_DeltaTime;
	FLOAT64 m_FixedTickRate;
	FLOAT64 m_FixedDeltaTime;

	GameRenderer m_GameRenderer;
	EventManager m_EventManager;
};
#endif // !GAME_H
