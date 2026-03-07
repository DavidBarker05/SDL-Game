#ifndef INPUTMANAGER_H

#include "EventListener.h"
#include "DataTypes.h"

class InputManager : public EventListener
{
public:
	virtual void HandleEvent(const SDL_Event& event) override;

private:
	void DoKeyDown(UINT32 keyCode);
	void DoKeyUp(UINT32 keyCode);
};
#endif // !INPUTMANAGER_H
