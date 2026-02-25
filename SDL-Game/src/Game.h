#pragma once
#include "InputManager.h"

class Game
{
	struct SDL_Window* m_Window;
	struct SDL_Renderer* m_Renderer;

	bool m_GameIsRunning;

	InputManager m_InputManager;

public:
	Game(const char* title, int width, int height);
	~Game();

	void Run();

private:
	void RenderGame();
};
