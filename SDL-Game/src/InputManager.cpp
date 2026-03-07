#include "InputManager.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_log.h>

void InputManager::HandleEvent(const SDL_Event& event)
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

void InputManager::DoKeyDown(UINT32 keyCode)
{
	switch (keyCode)
	{
		case SDLK_w:
			break;
		case SDLK_UP:
			break;
		case SDLK_s:
			break;
		case SDLK_DOWN:
			break;
		case SDLK_d:
			break;
		case SDLK_RIGHT:
			break;
		case SDLK_a:
			break;
		case SDLK_LEFT:
			break;
		default:
			break;
	}
}

void InputManager::DoKeyUp(UINT32 keyCode)
{
	switch (keyCode)
	{
		case SDLK_w:
			break;
		case SDLK_UP:
			break;
		case SDLK_s:
			break;
		case SDLK_DOWN:
			break;
		case SDLK_d:
			break;
		case SDLK_RIGHT:
			break;
		case SDLK_a:
			break;
		case SDLK_LEFT:
			break;
		default:
			break;
	}
}
