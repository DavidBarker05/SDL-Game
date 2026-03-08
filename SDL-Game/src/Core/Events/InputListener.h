#ifndef INPUTLISTENER_H
#define INPUTLISTENER_H

#include "InputManager.h"

class InputListener
{
public:
	virtual ~InputListener() = default;

	virtual void HandleInput(InputManager* pInputManager) = 0;
};
#endif // !INPUTLISTENER_H
