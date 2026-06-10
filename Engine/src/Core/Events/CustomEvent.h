#pragma once

#include "Event.h"
#include "Types.h"

class CustomEvent : public Event
{
public:
    CustomEvent(UINT64 eventID);
};
