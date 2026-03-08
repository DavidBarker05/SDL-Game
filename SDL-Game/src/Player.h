#ifndef PLAYER_H
#define PLAYER_H

#include "Core/DataTypes.h"
#include "Math/Vector2.h"
#include <SDL2/SDL_render.h>
#include "Entity.h"
#include "Events/InputListener.h"

class Game;

class Player : public Entity, public InputListener
{
public:
	typedef Entity Super;

	Player();

	virtual void HandleInput(InputManager* pInputManager) override;

	virtual void Tick(FLOAT32 deltaTime) override;
	virtual void Render(SDL_Renderer* pRenderer) override;

private:
	Vector2 m_Velocity;
};
#endif // !PLAYER_H
