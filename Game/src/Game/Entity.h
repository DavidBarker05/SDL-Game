#ifndef ENTITY_H
#define ENTITY_H

#include "Core.h"

class Entity
{
public:
    Entity(Vec2D position = Vec2D(0.0f, 0.0f), Vec2D halfExtents = Vec2D(0.0f, 0.0f));

    virtual void Tick(FLOAT32 deltaTime) { }

protected:
    Vec2D m_HalfExtents;
    Vec2D m_Position;
};
#endif // !ENTITY_H
