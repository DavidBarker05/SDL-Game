#ifndef PLAYER_H
#define PLAYER_H

#include "Core.h"
#include "SDLTypes.h"
#include "Box2DTypes.h"
#include "Entity.h"
#include "InputListener.h"

class Game;

class Player : public Entity, public InputListener
{
public:
	typedef Entity Super;

	Player();

	virtual void HandleInput(InputManager* pInputManager) override;

	virtual void Tick(FLOAT32 deltaTime) override;
	virtual void Render(P_RENDERER pRenderer) override;

private:
	VEC2D m_Velocity;
};
#endif // !PLAYER_H
