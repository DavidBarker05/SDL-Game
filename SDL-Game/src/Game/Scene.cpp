#include "Scene.h"
#include "InputListener.h"
#include "PhysicsEntity.h"
#include <box2d/box2d.h>

Scene::Scene() : m_pWorldDetails(new WorldDetails())
{
	m_pWorldDetails->worldDef = b2DefaultWorldDef();
	m_pWorldDetails->worldDef.gravity = VEC2D({ 0.0f, 10.0f });
	m_pWorldDetails->worldId = b2CreateWorld(&m_pWorldDetails->worldDef);

	PhysicsEntity* entity = new PhysicsEntity(m_pWorldDetails->worldId, TRUE, TRUE, NULL, VEC2D({ 0.0f, 0.0f }), VEC2D({ 25.0f, 25.0f }));
	AddEntity(entity);
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

void Scene::HandleEvent(EVENT event)
{
	for (Entity* pEntity : m_pEntities)
	{
		if (EventListener* pListener = Cast<EventListener>(pEntity))
		{
			pListener->HandleEvent(event);
		}
	}
}

void Scene::TickPhysics(FLOAT32 fixedDeltaTime)
{
	b2World_Step(m_pWorldDetails->worldId, fixedDeltaTime, 4);
	for (Entity* pEntity : m_pEntities)
	{
		if (PhysicsEntity* pPhysicsEntity = Cast<PhysicsEntity>(pEntity))
		{
			pPhysicsEntity->TickPhysics(fixedDeltaTime);
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

void Scene::Render(P_RENDERER pRenderer)
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
