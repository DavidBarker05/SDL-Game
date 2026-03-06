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

	void CreateWindow(CSTRING title, INT16 width, INT16 height, UINT32 flags);
	void CreateRenderer(INT16 index, UINT32 flags);

	void Render();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
};
#endif // !GAMERENDERER_H
