#ifndef GAME_H
#define GAME_H

#include "InputManager.h"
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
	InputManager m_InputManager;
};
#endif // !GAME_H
