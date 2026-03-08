#ifndef ENTITY_H
#define ENTITY_H

#include "Core.h"

class Entity
{
public:
	Entity(P_TEX2D pTexture = NULL, VEC2D position = VEC2D(0.0f, 0.0f), VEC2D halfExtents = VEC2D(0.0f, 0.0f));

	virtual void Tick(FLOAT32 deltaTime);
	virtual void Render(P_RENDERER pRenderer);

protected:
	P_TEX2D m_pTexture;

	VEC2D m_HalfExtents;
	VEC2D m_Position;
};
#endif // !ENTITY_H
