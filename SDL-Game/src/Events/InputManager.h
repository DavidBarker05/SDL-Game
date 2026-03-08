#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "../Core/DataTypes.h"
#include "EventListener.h"
#include "../Math/Vector2.h"

class InputManager : public EventListener
{
public:
	virtual void HandleEvent(const SDL_Event& event) override;

	Vector2 GetMoveInput();

private:
	void DoKeyDown(UINT32 keyCode);
	void DoKeyUp(UINT32 keyCode);
	Vector2 m_MoveInput;
};
#endif // !INPUTMANAGER_H
