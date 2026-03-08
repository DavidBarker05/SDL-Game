#include "EventManager.h"
#include "SDL2/SDL.h"

bool EventManager::Init()
{
	return !SDL_Init(SDL_INIT_EVENTS);
}

PollStatus EventManager::PollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) return PollStatus::eQUIT;
		m_InputManager.HandleEvent(event);
	}
	return PollStatus::eALL_EVENTS_POLLED;
}

InputManager& EventManager::GetInputManager() { return m_InputManager; }
