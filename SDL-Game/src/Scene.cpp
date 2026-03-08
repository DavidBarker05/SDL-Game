#include "Scene.h"
#include "Events/InputListener.h"

Scene::Scene() { }

void Scene::HandleInput(InputManager* pInputManager)
{
	for (Entity* pEntity : m_pEntities)
	{
		if (InputListener* pListener = dynamic_cast<InputListener*>(pEntity))
		{
			pListener->HandleInput(pInputManager);
		}
	}
}

void Scene::HandleEvent(SDL_Event event)
{
	for (Entity* pEntity : m_pEntities)
	{
		if (EventListener* pListener = dynamic_cast<EventListener*>(pEntity))
		{
			pListener->HandleEvent(event);
		}
	}
}

void Scene::Tick(FLOAT32 deltaTime)
{
	for (Entity* pEntity : m_pEntities)
	{
		pEntity->Tick(deltaTime);
	}
}

void Scene::Render(SDL_Renderer* pRenderer)
{
	for (Entity* pEntity : m_pEntities)
	{
		pEntity->Render(pRenderer);
	}
}

void Scene::AddEntity(Entity* pEntity)
{
	m_pEntities.emplace_back(pEntity);
}
