#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "DataTypes.h"
#include "EventListener.h"
#include "InputManager.h"
#include <vector>

enum class PollStatus : UINT8
{
	eALL_EVENTS_POLLED,
	eQUIT
};

class EventManager
{
public:
	void Init();

	PollStatus PollEvents();

	void SubscribeToEvents(const EventListener& listener);
	void UnsubscribeFromEvents(const EventListener& listener);

private:
	InputManager m_InputManager;
	std::vector<EventListener> m_EventListeners;
};
#endif // !EVENTMANAGER_H
