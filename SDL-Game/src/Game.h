#ifndef GAME_H
#define GAME_H

#include "EventManager.h"
#include "GameRenderer.h"
#include "DataTypes.h"

class Game
{
public:
	Game();
	~Game();

	void Init(CSTRING title, INT16 width, INT16 height);
	void Run();

private:
	bool m_bGameIsRunning;
	FLOAT32 m_DeltaTime;

	GameRenderer m_GameRenderer;
	EventManager m_EventManager;
};
#endif // !GAME_H
