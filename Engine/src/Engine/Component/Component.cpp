#include "Component.h"
#include "../Entity/Entity.h"

Component::Component() : Super(), m_pOwner(nullptr) { }

void Component::Attach(Entity* pOwner)
{
    if (IsValid(m_pOwner)) m_pOwner->RemoveComponent(this);
    m_pOwner = pOwner;
    if (IsValid(m_pOwner)) m_pOwner->AddComponent(this);
}

Entity* Component::Owner() { return m_pOwner; }
