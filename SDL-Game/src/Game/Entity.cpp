#include "Entity.h"

Entity::Entity(P_TEX2D pTexture, VEC2D position, VEC2D halfExtents) : m_pTexture(pTexture), m_Position(position), m_HalfExtents(halfExtents) { }

void Entity::Tick(FLOAT32 deltaTime) { }

void Entity::Render(P_RENDERER pRenderer)
{
	F_RECT2D r = { m_Position.x - m_HalfExtents.x, m_Position.y + m_HalfExtents.y, 2.0f * m_HalfExtents.x, 2.0f * m_HalfExtents.y };
	if (m_pTexture)
	{
		SDL_RenderCopyF(pRenderer, m_pTexture, NULL, &r);
	}
	else
	{
		SDL_SetRenderDrawColor(pRenderer, 255, 0, 255, 255);
		SDL_RenderFillRectF(pRenderer, &r);
	}
}