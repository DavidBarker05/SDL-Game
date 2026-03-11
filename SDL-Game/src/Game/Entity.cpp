#include "Entity.h"

Entity::Entity(SDL_Texture* pTexture, Vec2D position, Vec2D halfExtents) : m_pTexture(pTexture), m_Position(position), m_HalfExtents(halfExtents) { }

void Entity::Tick(FLOAT32 deltaTime) { }

void Entity::Render(SDL_Renderer* pRenderer)
{
	SDL_FRect r = { m_Position.x - m_HalfExtents.x, m_Position.y + m_HalfExtents.y, 2.0f * m_HalfExtents.x, 2.0f * m_HalfExtents.y };
	if (m_pTexture)
	{
		SDL_RenderTexture(pRenderer, m_pTexture, NULL, &r);
	}
	else
	{
		SDL_SetRenderDrawColor(pRenderer, 255, 0, 255, 255);
		SDL_RenderFillRect(pRenderer, &r);
	}
}