#pragma once

#include "Types.h"

class EventSystem
{
public:
	static constexpr UINT32 Quit = 0; // Code returned by PollEvents() when the game is closed
	static constexpr UINT32 AllEventsPolled = 1; // Code returned by PollEvents() when all events have been polled

public:
	// Initialise the event system. Returns true of success and false on fail
	static bool Init();
	// Shutdown the event system
	static void Shutdown();

	// Poll all the events
	static UINT32 PollEvents();
};
