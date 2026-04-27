#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "Core.h"

class EventManager
{
public:
	static constexpr UINT32 Quit = 0;
	static constexpr UINT32 AllEventsPolled = 1;

public:
	static bool Init();
	static void Shutdown();

	static UINT32 PollEvents();
};
#endif // !EVENTMANAGER_H
