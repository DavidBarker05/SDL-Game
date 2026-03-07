#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include "DataTypes.h"
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

class GameRenderer
{
public:
	void Init();
	void Destroy();

	void Render();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
};
#endif // !GAMERENDERER_H
