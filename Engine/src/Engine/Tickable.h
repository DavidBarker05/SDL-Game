#pragma once

#include "Types.h"

class Tickable
{
    virtual void Tick(FLOAT32 deltaTime) = 0;
};
