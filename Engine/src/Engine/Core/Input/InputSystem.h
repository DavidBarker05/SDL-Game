#pragma once

#include "Math/Vector2D.h"
#include <SDL3/SDL_events.h>

class InputSystem
{
public:
	static void HandleInput(const SDL_Event& event);

	static Vector2 GetMoveInput();

private:
	static void DoKeyDown(SDL_Keycode keyCode);
	static void DoKeyUp(SDL_Keycode keyCode);
};
