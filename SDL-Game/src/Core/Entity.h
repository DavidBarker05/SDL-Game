#ifndef ENTITY_H
#define ENTITY_H

#include "DataTypes.h"
#include "Vector2.h"
#include <SDL2/SDL_render.h>

class Entity
{
public:
	Entity();

	virtual void Tick(FLOAT32 deltaTime);
	virtual void Render(SDL_Renderer* pRenderer);

protected:
	SDL_Texture* m_Texture;

	Vector2 m_Position;
};
#endif // !ENTITY_H
