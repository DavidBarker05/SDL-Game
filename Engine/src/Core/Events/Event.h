#pragma once

class Event
{
protected:
    Event() = default;
    Event(const Event& other) = delete;
    Event(Event&& other) = delete;

public:
    virtual ~Event() = default;
};
