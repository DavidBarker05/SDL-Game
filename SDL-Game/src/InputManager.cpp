#include "InputManager.h"
#include <SDL2/SDL_events.h>

void InputManager::HandleEvent(const SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
			DoKeyDown(event.key.keysym.sym);
			break;
		case SDL_KEYUP:
			DoKeyUp(event.key.keysym.sym);
			break;
		default:
			break;
	}
}

Vector2 InputManager::GetMoveInput() { return m_MoveInput; }

void InputManager::DoKeyDown(UINT32 keyCode)
{
	switch (keyCode)
	{
		case SDLK_w:
			if (m_MoveInput.y == 1) m_MoveInput.y = 0;
			else m_MoveInput.y = -1;
			break;
		case SDLK_UP:
			if (m_MoveInput.y == 1) m_MoveInput.y = 0;
			else m_MoveInput.y = -1;
			break;
		case SDLK_s:
			if (m_MoveInput.y == -1) m_MoveInput.y = 0;
			else m_MoveInput.y = 1;
			break;
		case SDLK_DOWN:
			if (m_MoveInput.y == -1) m_MoveInput.y = 0;
			else m_MoveInput.y = 1;
			break;
		case SDLK_d:
			if (m_MoveInput.x == -1) m_MoveInput.x = 0;
			else m_MoveInput.x = 1;
			break;
		case SDLK_RIGHT:
			if (m_MoveInput.x == -1) m_MoveInput.x = 0;
			else m_MoveInput.x = 1;
			break;
		case SDLK_a:
			if (m_MoveInput.x == 1) m_MoveInput.x = 0;
			else m_MoveInput.x = -1;
			break;
		case SDLK_LEFT:
			if (m_MoveInput.x == 1) m_MoveInput.x = 0;
			else m_MoveInput.x = -1;
			break;
		default:
			break;
	}
}

void InputManager::DoKeyUp(UINT32 keyCode)
{
	switch (keyCode)
	{
		case SDLK_w:
			if (m_MoveInput.y == -1) m_MoveInput.y = 0;
			else if (m_MoveInput.y == 0) m_MoveInput.y = 1;
			break;
		case SDLK_UP:
			if (m_MoveInput.y == -1) m_MoveInput.y = 0;
			else if (m_MoveInput.y == 0) m_MoveInput.y = 1;
			break;
		case SDLK_s:
			if (m_MoveInput.y == 1) m_MoveInput.y = 0;
			else if (m_MoveInput.y == 0) m_MoveInput.y = -1;
			break;
		case SDLK_DOWN:
			if (m_MoveInput.y == 1) m_MoveInput.y = 0;
			else if (m_MoveInput.y == 0) m_MoveInput.y = -1;
			break;
		case SDLK_d:
			if (m_MoveInput.x == 1) m_MoveInput.x = 0;
			else if (m_MoveInput.x == 0) m_MoveInput.x = -1;
			break;
		case SDLK_RIGHT:
			if (m_MoveInput.x == 1) m_MoveInput.x = 0;
			else if (m_MoveInput.x == 0) m_MoveInput.y = -1;
			break;
		case SDLK_a:
			if (m_MoveInput.x == -1) m_MoveInput.x = 0;
			else if (m_MoveInput.x == 0) m_MoveInput.y = 1;
			break;
		case SDLK_LEFT:
			if (m_MoveInput.x == -1) m_MoveInput.x = 0;
			else if (m_MoveInput.x == 0) m_MoveInput.x = 1;
			break;
		default:
			break;
	}
}
