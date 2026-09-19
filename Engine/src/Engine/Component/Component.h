#pragma once

#include "../Object/Object.h"
#include "Core.h"

class Entity;

class Component : public Object
{
public:
    Component();
    virtual ~Component() = default;

public:
    virtual void Attach(std::shared_ptr<Entity> spOwner);
    std::shared_ptr<Entity> Owner();

private:
    std::shared_ptr<Entity> m_spOwner;
};
