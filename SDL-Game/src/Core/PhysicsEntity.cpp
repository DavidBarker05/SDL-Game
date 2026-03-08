#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(WORLD_ID worldId, bool bUseGravity, bool bIsKinematic, P_TEX2D pTexture, VEC2D position, VEC2D halfExtents) : Super(pTexture, position, halfExtents), m_pBodyDetails(new BodyDetails())
{
	//Super(pTexture, position, halfExtents);
	m_pBodyDetails->bodyDef = b2DefaultBodyDef();
	if (bIsKinematic)
	{
		if (bUseGravity) m_pBodyDetails->bodyDef.type = b2_dynamicBody;
		else m_pBodyDetails->bodyDef.type = b2_kinematicBody;
	}
	else m_pBodyDetails->bodyDef.type = b2_staticBody;
	m_pBodyDetails->bodyDef.position = position;
	m_pBodyDetails->bodyId = b2CreateBody(worldId, &m_pBodyDetails->bodyDef);
	m_pBodyDetails->polygon = b2MakeBox(halfExtents.x, halfExtents.y);
	m_pBodyDetails->shapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(m_pBodyDetails->bodyId, &m_pBodyDetails->shapeDef, &m_pBodyDetails->polygon);
}

void PhysicsEntity::TickPhysics(FLOAT32 fixedDeltaTime)
{
	m_Position = b2Body_GetPosition(m_pBodyDetails->bodyId);
}

void PhysicsEntity::Tick(FLOAT32 deltaTime)
{
}

void PhysicsEntity::Render(P_RENDERER pRenderer)
{
	Super::Render(pRenderer);
}
