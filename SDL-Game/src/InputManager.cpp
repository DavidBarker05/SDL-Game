#include "InputManager.h"
#include <SDL.h>

void InputManager::ProcessEvent(const SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
			DoKeyDown(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			DoKeyUp(event.key.keysym.sym);
			break;
		default:
			break;
	}
}

void InputManager::DoKeyDown(int32_t keyCode)
{
	switch (keyCode)
	{
		default:
			break;
	}
}

void InputManager::DoKeyUp(int32_t keyCode)
{
	switch (keyCode)
	{
		default:
			break;
	}
}
