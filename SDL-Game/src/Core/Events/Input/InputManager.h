#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Core.h"
#include <SDL3/SDL_events.h>

class InputManager
{
public:
	static void HandleInput(const SDL_Event& event);
	//virtual void HandleEvent(const SDL_Event& event) override;

	static Vec2D GetMoveInput();

private:
	static void DoKeyDown(SDL_Keycode keyCode);
	static void DoKeyUp(SDL_Keycode keyCode);
};
#endif // !INPUTMANAGER_H
