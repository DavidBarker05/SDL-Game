#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "DataTypes.h"
#include <vector>
#include <memory>
#include "InputManager.h"
#include "EventListener.h"

enum class PollStatus : UINT8
{
	eALL_EVENTS_POLLED,
	eQUIT
};

enum class CustomEvent : INT32
{
};

class EventManager
{
public:
	void Init();

	PollStatus PollEvents();

	void SubscribeListenerToEvents(std::weak_ptr<EventListener> wpListener);
	void SubscribeListenerToEvents(std::shared_ptr<EventListener> spListener);

	void UnsubscribeListenerFromEvents(std::weak_ptr<EventListener> wpListener);
	void UnsubscribeListenerFromEvents(std::shared_ptr<EventListener> spListener);

	InputManager* GetInputManager();

private:
	std::unique_ptr<InputManager> m_upInputManager;
	std::vector<std::weak_ptr<EventListener>> m_wpEventListeners;
};
#endif // !EVENTMANAGER_H
