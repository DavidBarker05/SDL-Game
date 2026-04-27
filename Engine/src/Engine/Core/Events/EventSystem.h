#pragma once

#include "Types.h"

class EventSystem
{
public:
	static constexpr UINT32 Quit = 0;
	static constexpr UINT32 AllEventsPolled = 1;

public:
	static bool Init();
	static void Shutdown();

	static UINT32 PollEvents();
};
