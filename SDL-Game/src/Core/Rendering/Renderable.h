#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "GameRenderer.h"

class Renderable
{
public:
	~Renderable() = default;

	virtual void Render(GameRenderer& gameRenderer) = 0;
};
#endif // !RENDERABLE_H
