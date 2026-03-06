#include "InputManager.h"
#include "SDL2/SDL.h"

void InputManager::Init()
{
	SDL_Init(SDL_INIT_EVENTS);
}

PollStatus InputManager::PollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				return PollStatus::QUIT;
				break;
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
	return PollStatus::ALL_EVENTS_POLLED;
}

void InputManager::DoKeyDown(Uint32 keyCode)
{
	switch (keyCode)
	{
		default:
			break;
	}
}

void InputManager::DoKeyUp(Uint32 keyCode)
{
	switch (keyCode)
	{
		default:
			break;
	}
}
