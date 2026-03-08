#include "Entity.h"

Entity::Entity() : m_Texture(NULL), m_Position()
{

}

void Entity::Tick(FLOAT32 deltaTime) { }

void Entity::Render(SDL_Renderer* pRenderer)
{
	SDL_Rect r = { m_Position.x, m_Position.y, 50, 50 };
	if (m_Texture)
	{
		SDL_RenderCopy(pRenderer, m_Texture, NULL, &r);
	}
	else
	{
		SDL_SetRenderDrawColor(pRenderer, 255, 0, 255, 255);
		SDL_RenderFillRect(pRenderer, &r);
	}
}