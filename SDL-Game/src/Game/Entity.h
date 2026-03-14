#ifndef ENTITY_H
#define ENTITY_H

#include "Core.h"
#include "Renderable.h"

class Entity : public Renderable
{
public:
	Entity(SDL_Texture* pTexture = nullptr, Vec2D position = Vec2D(0.0f, 0.0f), Vec2D halfExtents = Vec2D(0.0f, 0.0f));

	virtual void Tick(FLOAT32 deltaTime);
	virtual void Render(SDL_Renderer* pRenderer) override;

protected:
	SDL_Texture* m_pTexture;

	Vec2D m_HalfExtents;
	Vec2D m_Position;
};
#endif // !ENTITY_H
