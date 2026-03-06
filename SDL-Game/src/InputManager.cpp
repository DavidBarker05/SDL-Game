#include "EventManager.h"
#include "SDL2/SDL.h"

void EventManager::Init()
{
	SDL_Init(SDL_INIT_EVENTS);
}

PollStatus EventManager::PollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				return PollStatus::eQUIT;
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
	return PollStatus::eALL_EVENTS_POLLED;
}

void EventManager::DoKeyDown(Uint32 keyCode)
{
	switch (keyCode)
	{
		default:
			break;
	}
}

void EventManager::DoKeyUp(Uint32 keyCode)
{
	switch (keyCode)
	{
		default:
			break;
	}
}
