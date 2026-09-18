#pragma once

#include "../Object/Object.h"
#include "Core.h"
#include <type_traits>
#include <vector>

class Component;

class Entity final : public Object
{
public:
    typedef Object Super;

    template<typename T, std::enable_if_t<std::is_base_of_v<T, Component>, int> = 0>
    std::shared_ptr<T> AddComponent()
    {
        std::shared_ptr<T> spComponent = std::make_shared<T>();
        m_Components.emplace_back(spComponent);
        return spComponent;
    }

    void AddComponent(std::shared_ptr<Component> pComponent);

    void AddComponent(Component* pComponent);

    void RemoveComponent(std::shared_ptr<Component> spComponent);

    void RemoveComponent(Component* pComponent);

public:
    Vector2 GetPosition();
    void SetPosition(const Vector2& position);

protected:
    Vector2 m_Position {};

private:
    std::vector<std::shared_ptr<Component>> m_Components;
};
