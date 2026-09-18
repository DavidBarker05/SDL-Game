#include "Entity.h"
#include "../Component/Component.h"
#include <algorithm>

void Entity::AddComponent(std::shared_ptr<Component> spComponent)
{
    if (!spComponent) return;
    if (std::find(m_Components.begin(), m_Components.end(), spComponent) == m_Components.end())
        m_Components.emplace_back(spComponent);
}

void Entity::AddComponent(Component* pComponent)
{
    if (!pComponent) return;
    if (std::find_if(m_Components.begin(), m_Components.end(),
                     [pComponent](const std::shared_ptr<Component>& spComponent) -> bool
                     { return spComponent.get() == pComponent; }) != m_Components.end())
        return;
    std::shared_ptr<Component> spComponent(pComponent);
    m_Components.emplace_back(spComponent);
}

void Entity::RemoveComponent(std::shared_ptr<Component> spComponent)
{
    if (spComponent) m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), spComponent));
}

void Entity::RemoveComponent(Component* pComponent)
{
    if (!pComponent) return;
    m_Components.erase(std::remove_if(m_Components.begin(), m_Components.end(),
                                      [pComponent](const std::shared_ptr<Component>& spComponent) -> bool
                                      { return spComponent.get() == pComponent; }),
                       m_Components.end());
}

Vector2 Entity::GetPosition() { return m_Position; }

void Entity::SetPosition(const Vector2& position) { m_Position = position; }
