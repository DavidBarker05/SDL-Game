#include "EventManager.h"
#include <SDL2/SDL.h>
#include "Scene.h"

bool EventManager::Init()
{
	return !SDL_Init(SDL_INIT_EVENTS);
}

PollStatus EventManager::PollEvents()
{
	EVENT event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) return PollStatus::eQUIT;
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
