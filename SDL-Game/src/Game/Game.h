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

private:
	void Tick();

	void UpdateDeltaTime();

	bool m_bGameIsRunning;
	UINT64 m_CurrentFrameTime;
	UINT64 m_LastFrameTime;
	FLOAT64 m_DeltaTime;

	GameRenderer m_GameRenderer;
	EventManager m_EventManager;
};
#endif // !GAME_H
