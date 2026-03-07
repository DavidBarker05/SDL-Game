#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "DataTypes.h"
#include "EventListener.h"
#include "InputManager.h"
#include <vector>
#include <memory>

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

	void SubscribeListenerToEvents(std::weak_ptr<EventListener> pListener);
	void SubscribeListenerToEvents(std::shared_ptr<EventListener> pListener);

	void UnsubscribeListenerFromEvents(std::weak_ptr<EventListener> pListener);
	void UnsubscribeListenerFromEvents(std::shared_ptr<EventListener> pListener);

private:
	InputManager m_InputManager;
	std::vector<std::weak_ptr<EventListener>> m_pEventListeners;
};
#endif // !EVENTMANAGER_H
