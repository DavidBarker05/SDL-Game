#ifndef GAME_H
#define GAME_H

#include "DataTypes.h"
#include "GameRenderer.h"
#include "EventManager.h"

class Game
{
public:
	Game();
	~Game();

	void Init();
	void Start();

	GameRenderer& GetGameRenderer();
	EventManager& GetEventManager();

private:
	void Tick();

	bool m_bGameIsRunning;
	FLOAT32 m_CurrentFrameTime;
	FLOAT32 m_LastFrameTime;
	FLOAT32 m_DeltaTime;

	GameRenderer m_GameRenderer;
	EventManager m_EventManager;
};
#endif // !GAME_H
