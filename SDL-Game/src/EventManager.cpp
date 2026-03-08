#include "EventManager.h"
#include "SDL2/SDL.h"
#include <algorithm>

void EventManager::Init()
{
	SDL_Init(SDL_INIT_EVENTS);
	m_upInputManager = std::make_unique<InputManager>();
}

PollStatus EventManager::PollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) return PollStatus::eQUIT;
		m_upInputManager->HandleEvent(event);
		std::vector<std::weak_ptr<EventListener>>::iterator it = m_wpEventListeners.begin();
		while (it != m_wpEventListeners.end())
		{
			if (std::shared_ptr<EventListener> pListener = (*it).lock())
			{
				pListener->HandleEvent(event);
				++it;
			}
			else it = m_wpEventListeners.erase(it);
		}
	}
	return PollStatus::eALL_EVENTS_POLLED;
}

void EventManager::SubscribeListenerToEvents(std::weak_ptr<EventListener> wpListener)
{
	if (std::find_if(m_wpEventListeners.begin(), m_wpEventListeners.end(), [wpListener](std::weak_ptr<EventListener> wpOther) -> bool { return wpListener.owner_before(wpOther); }) == m_wpEventListeners.end());
		m_wpEventListeners.emplace_back(wpListener);
}

void EventManager::SubscribeListenerToEvents(std::shared_ptr<EventListener> spListener) { SubscribeListenerToEvents(std::weak_ptr<EventListener>(spListener)); }

void EventManager::UnsubscribeListenerFromEvents(std::weak_ptr<EventListener> wpListener)
{
	m_wpEventListeners.erase(std::remove_if(m_wpEventListeners.begin(), m_wpEventListeners.end(), [wpListener](std::weak_ptr<EventListener> wpOther) -> bool { return wpListener.owner_before(wpOther); }), m_wpEventListeners.end());
}

void EventManager::UnsubscribeListenerFromEvents(std::shared_ptr<EventListener> spListener) { UnsubscribeListenerFromEvents(std::weak_ptr<EventListener>(spListener)); }

InputManager* EventManager::GetInputManager() { return m_upInputManager.get(); }
