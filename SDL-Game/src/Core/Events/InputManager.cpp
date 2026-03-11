#include "InputManager.h"

void InputManager::HandleEvent(const SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_EVENT_KEY_DOWN:
			DoKeyDown(event.key.key);
			break;
		case SDL_EVENT_KEY_UP:
			DoKeyUp(event.key.key);
			break;
		default:
			break;
	}
}

Vec2D InputManager::GetMoveInput()
{
	const bool* keys = SDL_GetKeyboardState(NULL);
	UINT8 up = keys[SDL_SCANCODE_W] | keys[SDL_SCANCODE_UP];
	UINT8 down = keys[SDL_SCANCODE_S] | keys[SDL_SCANCODE_DOWN];
	UINT8 right = keys[SDL_SCANCODE_D] | keys[SDL_SCANCODE_RIGHT];
	UINT8 left = keys[SDL_SCANCODE_A] | keys[SDL_SCANCODE_LEFT];
	FLOAT32 y = up && !down ? -1.0f : (down && !up ? 1.0f : 0.0f);
	FLOAT32 x = right && !left ? 1.0f : (left && !right ? -1.0f : 0.0f);
	m_MoveInput.y = y;
	m_MoveInput.x = x;
	return m_MoveInput;
}

void InputManager::DoKeyDown(SDL_Keycode keyCode)
{
	switch (keyCode)
	{
		default:
			break;
	}
}

void InputManager::DoKeyUp(SDL_Keycode keyCode)
{
	switch (keyCode)
	{
		default:
			break;
	}
}
