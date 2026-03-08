#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "SDLTypes.h"

class EventListener
{
public:
	virtual ~EventListener() = default;

	virtual void HandleEvent(const EVENT& event) = 0;
};
#endif // !EVENTLISTENER_H
