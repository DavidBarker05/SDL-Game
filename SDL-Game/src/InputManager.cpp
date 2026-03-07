#include "InputManager.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>

void InputManager::HandleEvent(const SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
			SDL_Log("aaa");
			DoKeyDown(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			DoKeyUp(event.key.keysym.sym);
			break;
		default:
			break;
	}
}

void InputManager::DoKeyDown(UINT32 keyCode)
{
	switch (keyCode)
	{
		default:
			break;
	}
}

void InputManager::DoKeyUp(UINT32 keyCode)
{
	switch (keyCode)
	{
		default:
			break;
	}
}
