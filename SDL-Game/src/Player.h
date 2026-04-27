#ifndef PLAYER_H
#define PLAYER_H

#include "Core.h"
#include "Entity.h"
#include <SDL3/SDL_render.h>

class Game;

class Player : public Entity
{
public:
	typedef Entity Super;

	Player();

	virtual void Tick(FLOAT32 deltaTime) override;
	virtual void Render(SDL_Renderer* pRenderer) override;

private:
	Vec2D m_Velocity;
};
#endif // !PLAYER_H
