#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "DataTypes.h"

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

private:
	
	void DoKeyDown(UINT32 keyCode);
	void DoKeyUp(UINT32 keyCode);
};
#endif // !EVENTMANAGER_H
