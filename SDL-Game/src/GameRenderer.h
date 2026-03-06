#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

class GameRenderer
{
public:
	void Init();
	void Destroy();

	void CreateWindow(const char* title, int width, int height, Uint32 flags);
	void CreateRenderer(int index, Uint32 flags);

	void Render();

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
};
#endif // !GAMERENDERER_H
