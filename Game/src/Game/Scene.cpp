#include "Scene.h"

Scene::Scene() { }

// void Scene::HandleEvent(const SDL_Event& event)
//{
//	for (Entity* pEntity : m_pEntities)
//	{
//		if (EventListener* pListener = Cast<EventListener>(pEntity))
//		{
//			pListener->HandleEvent(event);
//		}
//	}
// }

void Scene::Tick(FLOAT32 deltaTime)
{
    for (Entity* pEntity : m_pEntities)
    {
        pEntity->Tick(deltaTime);
    }
}

void Scene::AddEntity(Entity* pEntity) { m_pEntities.emplace_back(pEntity); }
