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
		std::vector<std::weak_ptr<EventListener>>::iterator it = m_pEventListeners.begin();
		while (it != m_pEventListeners.end())
		{
			if (std::shared_ptr<EventListener> pListener = (*it).lock())
			{
				pListener->HandleEvent(event);
				++it;
			}
			else it = m_pEventListeners.erase(it);
		}
	}
	return PollStatus::eALL_EVENTS_POLLED;
}

void EventManager::SubscribeListenerToEvents(std::weak_ptr<EventListener> pListener)
{
	if (std::find_if(m_pEventListeners.begin(), m_pEventListeners.end(), [pListener](std::weak_ptr<EventListener> pOther) -> bool { return pListener.owner_before(pOther); }) == m_pEventListeners.end());
		m_pEventListeners.emplace_back(pListener);
}

void EventManager::SubscribeListenerToEvents(std::shared_ptr<EventListener> pListener) { SubscribeListenerToEvents(std::weak_ptr<EventListener>(pListener)); }

void EventManager::UnsubscribeListenerFromEvents(std::weak_ptr<EventListener> pListener)
{
	m_pEventListeners.erase(std::remove_if(m_pEventListeners.begin(), m_pEventListeners.end(), [pListener](std::weak_ptr<EventListener> pOther) -> bool { return pListener.owner_before(pOther); }), m_pEventListeners.end());
}

void EventManager::UnsubscribeListenerFromEvents(std::shared_ptr<EventListener> pListener) { UnsubscribeListenerFromEvents(std::weak_ptr<EventListener>(pListener)); }
