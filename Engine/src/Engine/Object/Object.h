#pragma once

#include "Types.h"

class Object
{
public:
    Object();
    virtual ~Object();

    virtual void Tick(FLOAT32 deltaTime) = 0;
};
