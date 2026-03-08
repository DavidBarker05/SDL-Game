#ifndef PHYSICSENTITY_H
#define PHYSICSENTITY_H

#include "DataTypes.h"
#include "Entity.h"

typedef struct
{
	BODY_DEF bodyDef;
	BODY_ID bodyId;
	POLY2D polygon;
	SHAPE_DEF shapeDef;
} PhysicsDetails, BodyDetails, ShapeDetails;

class PhysicsEntity : public Entity
{
public:
	typedef Entity Super;

	PhysicsEntity(WORLD_ID worldId, bool bUseGravity = FALSE, bool bIsKinematic = FALSE , P_TEX2D pTexture = NULL, VEC2D position = VEC2D(0.0f, 0.0f), VEC2D halfExtents = VEC2D(0.0f, 0.0f));

	virtual void TickPhysics(FLOAT32 fixedDeltaTime);
	virtual void Tick(FLOAT32 deltaTime) override;
	virtual void Render(P_RENDERER pRenderer) override;

private:
	BodyDetails* m_pBodyDetails;
};
#endif // !PHYSICSENTITY_H
