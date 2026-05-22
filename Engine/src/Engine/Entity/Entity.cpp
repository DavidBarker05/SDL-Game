#include "Entity.h"
#include "../Component/Component.h"
#include <algorithm>

Entity::Entity() : Super(), m_Position() { }

void Entity::AddComponent(Component* pComponent)
{
    if (IsValid(pComponent) &&
        std::find(m_pComponents.begin(), m_pComponents.end(), pComponent) == m_pComponents.end())
        m_pComponents.emplace_back(pComponent);
}

void Entity::RemoveComponent(Component* pComponent)
{
    if (pComponent)
        m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), pComponent),
                            m_pComponents.end());
}

Vector2 Entity::GetPosition() { return m_Position; }

void Entity::SetPosition(const Vector2& position) { m_Position = position; }
