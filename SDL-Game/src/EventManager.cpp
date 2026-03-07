#include "EventManager.h"
#include "SDL2/SDL.h"
#include <algorithm>

void EventManager::Init()
{
	SDL_Init(SDL_INIT_EVENTS);
}

PollStatus EventManager::PollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) return PollStatus::eQUIT;
		m_InputManager.HandleEvent(event);
		for (auto it = m_EventListeners.rbegin(); it < m_EventListeners.rend(); ++it)
			it->HandleEvent(event);
	}
	return PollStatus::eALL_EVENTS_POLLED;
}

void EventManager::SubscribeToEvents(EventListener& listener)
{
	if (std::find(m_EventListeners.begin(), m_EventListeners.end(), listener) != m_EventListeners.end())
		m_EventListeners.emplace_back(&listener);
}

void EventManager::UnsubscribeFromEvents(EventListener& listener)
{
	m_EventListeners.erase(std::remove(m_EventListeners.begin(), m_EventListeners.end(), listener), m_EventListeners.end());
}
