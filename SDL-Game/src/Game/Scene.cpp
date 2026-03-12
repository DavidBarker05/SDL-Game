#include "Scene.h"
#include "InputListener.h"

Scene::Scene()
{
	
}

void Scene::HandleInput(InputManager* pInputManager)
{
	for (Entity* pEntity : m_pEntities)
	{
		if (InputListener* pListener = Cast<InputListener>(pEntity))
		{
			pListener->HandleInput(pInputManager);
		}
	}
}

void Scene::HandleEvent(const SDL_Event& event)
{
	for (Entity* pEntity : m_pEntities)
	{
		if (EventListener* pListener = Cast<EventListener>(pEntity))
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

void Scene::Render(GameRenderer& gameRenderer)
{
	for (Entity* pEntity : m_pEntities)
	{
		pEntity->Render(gameRenderer);
	}
}

void Scene::AddEntity(Entity* pEntity)
{
	m_pEntities.emplace_back(pEntity);
}
