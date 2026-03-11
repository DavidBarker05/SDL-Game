#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Core.h"
#include "EventListener.h"
#include <SDL2/SDL_events.h>

class InputManager : public EventListener
{
public:
	virtual void HandleEvent(const SDL_Event& event) override;

	Vec2D GetMoveInput();

private:
	void DoKeyDown(UINT32 keyCode);
	void DoKeyUp(UINT32 keyCode);
	Vec2D m_MoveInput;
};
#endif // !INPUTMANAGER_H
