#pragma once

#include <cstdint>

class InputManager
{
public:
	void ProcessEvent(const union SDL_Event& event);

private:
	void DoKeyDown(int32_t keyCode);
	void DoKeyUp(int32_t keyCode);
};
