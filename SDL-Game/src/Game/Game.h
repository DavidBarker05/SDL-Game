#ifndef GAME_H
#define GAME_H

#include "Core.h"
#include "GameRenderer.h"

class Game
{
public:
	bool Init();
	void Shutdown();

	void Start();

private:
	void Tick();

	void UpdateDeltaTime();

	bool m_bGameIsRunning = false;
	UINT64 m_CurrentFrameTime = 0;
	UINT64 m_LastFrameTime = 0;
	FLOAT64 m_DeltaTime = 0;

	GameRenderer m_GameRenderer;
};
#endif // !GAME_H
