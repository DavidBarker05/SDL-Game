#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <SDL2/SDL_events.h>

class EventListener
{
public:
	virtual ~EventListener() = default;

	virtual void HandleEvent(const SDL_Event& event) = 0;
};
#endif // !EVENTLISTENER_H
