#ifndef PLAYER_H
#define PLAYER_H

#include "DataTypes.h"
#include "Vector2.h"
#include <SDL2/SDL_render.h>

class Game;

class Player
{
public:
	Player(Game* pGame);

	void Start();
	void Tick(FLOAT32 deltaTime);
	void Render(SDL_Renderer* pRenderer);

private:
	Game* m_pGame;

	Vector2 m_Position;
	Vector2 m_Velocity;
};
#endif // !PLAYER_H
