#include "Events/EventSystem.h"
#include <SDL3/SDL_init.h>
#include "Logging/Log.h"
#include "Input/InputSystem.h"

bool EventSystem::Init()
{
	if (!SDL_Init(SDL_INIT_EVENTS))
	{
		LOG_FATAL("%s", SDL_GetError());
		return false;
	}
	LOG_INFO("Initialised the event manager");
	return true;
}

void EventSystem::Shutdown()
{
	// Nothing for now but might be needed later
}

UINT32 EventSystem::PollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT) return Quit;
		InputSystem::HandleInput(event);
	}
	return AllEventsPolled;
}