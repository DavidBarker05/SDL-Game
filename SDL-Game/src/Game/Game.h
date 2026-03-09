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

	bool m_bGameIsRunning;
	FLOAT32 m_CurrentFrameTime;
	FLOAT32 m_LastFrameTime;
	FLOAT32 m_DeltaTime;
	FLOAT32 m_FixedTickRate;
	FLOAT32 m_FixedDeltaTime;

	GameRenderer m_GameRenderer;
	EventManager m_EventManager;
};
#endif // !GAME_H
