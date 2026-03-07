#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "DataTypes.h"
#include "EventListener.h"
#include "InputManager.h"
#include <vector>
#include <unordered_map>

enum class PollStatus : UINT8
{
	eALL_EVENTS_POLLED,
	eQUIT
};

enum class CustomEvent : UINT64
{

};

class EventManager
{
public:
	void Init();

	PollStatus PollEvents();

	void SubscribeToEvents(EventListener& listener);
	void UnsubscribeFromEvents(EventListener& listener);

private:
	InputManager m_InputManager;
	std::vector<EventListener> m_EventListeners;
};
#endif // !EVENTMANAGER_H
