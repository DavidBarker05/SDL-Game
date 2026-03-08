#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "DataTypes.h"
#include "InputManager.h"

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

	InputManager& GetInputManager();

private:
	InputManager m_InputManager;
};
#endif // !EVENTMANAGER_H
