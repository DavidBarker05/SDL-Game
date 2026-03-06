#ifndef GAME_H
#define GAME_H

#include "EventManager.h"
#include "GameRenderer.h"

class Game
{
public:
	Game();
	~Game();

	void Init(const char* title, int width, int height);
	void Run();

private:
	bool m_GameIsRunning;

	GameRenderer m_GameRenderer;
	EventManager m_EventManager;
};
#endif // !GAME_H
