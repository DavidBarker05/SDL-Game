#pragma once

#include "../Object/Object.h"
#include "Core.h"
#include <type_traits>
#include <vector>

class Component;

class Entity final : public Object
{
public:
    void AddComponent(std::shared_ptr<Component> spComponent);

    void RemoveComponent(std::shared_ptr<Component> spComponent);

public:
    Vector2 GetPosition();
    void SetPosition(const Vector2& position);

protected:
    Vector2 m_Position {};

private:
    std::vector<std::shared_ptr<Component>> m_Components;
};
