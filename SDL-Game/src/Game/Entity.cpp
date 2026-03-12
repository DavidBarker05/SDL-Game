#include "Entity.h"

Entity::Entity(SDL_Texture* pTexture, Vec2D position, Vec2D halfExtents) : m_pTexture(pTexture), m_Position(position), m_HalfExtents(halfExtents) { }

void Entity::Tick(FLOAT32 deltaTime) { }

void Entity::Render(GameRenderer& gameRenderer)
{
	if (m_pTexture) gameRenderer.RenderTexture(m_pTexture, m_Position, m_HalfExtents);
	else gameRenderer.RenderRectangle(m_Position, m_HalfExtents, 255, 0, 255, 255);
}