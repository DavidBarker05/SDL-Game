#include "EventManager.h"
#include <SDL3/SDL_init.h>
#include "Scene.h"

bool EventManager::Init()
{
	if (!SDL_Init(SDL_INIT_EVENTS)) return FALSE;
	LOG_INFO("Initialised the event system");
	return TRUE;
}

PollStatus EventManager::PollEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_EVENT_QUIT) return PollStatus::eQUIT;
		m_InputManager.HandleEvent(event);
		if (m_pScene) m_pScene->HandleInput(&m_InputManager);
		if (m_pScene) m_pScene->HandleEvent(event);
	}
	return PollStatus::eALL_EVENTS_POLLED;
}

InputManager& EventManager::GetInputManager() { return m_InputManager; }

void EventManager::SetScene(Scene* pScene)
{
	m_pScene = pScene;
}
