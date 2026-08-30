#pragma once

#include "../Object/Object.h"
#include "Core.h"
#include <vector>

class Component;

class Entity final : public Object
{
public:
    typedef Object Super;

    Entity();

public:
    void Tick(FLOAT32 deltaTime) override { }

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
