#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <SDL3/SDL_render.h>

class Renderable
{
public:
	~Renderable() = default;

	virtual void Render(SDL_Renderer* pRenderer) = 0;
};
#endif // !RENDERABLE_H
