#include "Component.h"
#include "../Entity/Entity.h"

Component::Component() : m_spOwner(nullptr) { }

void Component::Attach(std::shared_ptr<Entity> spOwner)
{
    if (!spOwner) return;
    if (m_spOwner) m_spOwner->RemoveComponent(Cast<Component>(shared_from_this()));
    m_spOwner = spOwner;
    m_spOwner->AddComponent(Cast<Component>(shared_from_this()));
}

std::shared_ptr<Entity> Component::Owner() { return m_spOwner; }
