#pragma once

#include "../Object/Object.h"
#include "Core.h"
#include <type_traits>
#include <vector>

class Component;

class Entity final : public Object
{
    friend class Component;

public:
    template<typename T, std::enable_if_t<std::is_base_of_v<Component, T>, int> = 0>
    std::shared_ptr<T> CreateComponent()
    {
        std::shared_ptr<T> spComponent = ObjectSystem::Create<T>();
        m_Components.emplace_back(spComponent);
        return spComponent;
    }

private:
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
