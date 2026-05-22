#pragma once

#include "../Object/Object.h"
#include "../Tickable.h"
#include "Core.h"
#include <vector>

class Component;

class Entity : public Object,
               public Tickable
{
public:
    typedef Object Super;

    Entity();
    virtual ~Entity() { }

public:
    virtual void Tick(FLOAT32 deltaTime) override { }

public:
    void AddComponent(Component* pComponent);
    void RemoveComponent(Component* pComponent);

public:
    Vector2 GetPosition();
    void SetPosition(const Vector2& position);

protected:
    Vector2 m_Position;

private:
    std::vector<Component*> m_pComponents;
};
