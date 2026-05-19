#pragma once

#include "Types.h"

class Renderer
{
public:
	static bool Init(CSTRING title, UINT32 windowWidth, UINT32 windowHeight);
	static bool Init();
	static void Shutdown();

	static void Render();
};
