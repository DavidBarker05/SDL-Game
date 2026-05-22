#pragma once

#include "../Object/Object.h"

class Entity;

class Component : public Object
{
public:
    typedef Object Super;

    Component();

public:
    void Attach(Entity* pOwner);
    Entity* Owner();

private:
    Entity* m_pOwner;
};
