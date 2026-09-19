#pragma once

#include "../Object/Object.h"
#include "Core.h"

class Entity;

class Component : public Object
{
public:
    virtual void Attach(std::shared_ptr<Entity> spOwner);
    std::weak_ptr<Entity> Owner() { return m_wpOwner; }

private:
    std::weak_ptr<Entity> m_wpOwner;
};
