#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Core.h"
#include "EventListener.h"

class InputManager : public EventListener
{
public:
	virtual void HandleEvent(const EVENT& event) override;

	VEC2D GetMoveInput();

private:
	void DoKeyDown(UINT32 keyCode);
	void DoKeyUp(UINT32 keyCode);
	VEC2D m_MoveInput;
};
#endif // !INPUTMANAGER_H
