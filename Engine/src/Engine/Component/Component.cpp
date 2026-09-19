#include "Component.h"
#include "../Entity/Entity.h"

void Component::Attach(std::shared_ptr<Entity> spOwner)
{
    if (!spOwner) return;
    if (std::shared_ptr<Entity> spOriginalOwner = m_wpOwner.lock())
        spOriginalOwner->RemoveComponent(Cast<Component>(shared_from_this()));
    m_wpOwner = spOwner;
    spOwner->AddComponent(Cast<Component>(shared_from_this()));
}
