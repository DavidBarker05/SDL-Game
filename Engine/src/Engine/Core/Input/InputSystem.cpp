#include "InputSystem.h"

void InputSystem::HandleInput(const SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_EVENT_KEY_DOWN:
			DoKeyDown(event.key.key);
		case SDL_EVENT_KEY_UP:
			DoKeyUp(event.key.key);
		default:
			break;
	}
}

Vec2D InputSystem::GetMoveInput()
{
	const bool* keys = SDL_GetKeyboardState(nullptr);
	bool up = keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP];
	bool down = keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN];
	bool right = keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT];
	bool left = keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT];
	FLOAT32 y = up && !down ? -1.0f : (down && !up ? 1.0f : 0.0f);
	FLOAT32 x = right && !left ? 1.0f : (left && !right ? -1.0f : 0.0f);
	return Vec2D(x, y);
}

void InputSystem::DoKeyDown(SDL_Keycode keyCode)
{
	switch (keyCode)
	{
		default:
			break;
	}
}

void InputSystem::DoKeyUp(SDL_Keycode keyCode)
{
	switch (keyCode)
	{
		default:
			break;
	}
}