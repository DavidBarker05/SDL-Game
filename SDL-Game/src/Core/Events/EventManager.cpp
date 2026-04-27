#include "EventManager.h"
#include <SDL3/SDL_init.h>
#include "InputManager.h"

bool EventManager::Init()
{
	if (!SDL_Init(SDL_INIT_EVENTS))
	{
		LOG_FATAL("%s", SDL_GetError());
		return false;
	}
	LOG_INFO("Initialised the event manager");
	return true;
}

void EventManager::Shutdown()
{
	// Nothing for now but might be needed later
}

UINT32 EventManager::PollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT) return Quit;
		InputManager::HandleInput(event);
	}
	return AllEventsPolled;
}
