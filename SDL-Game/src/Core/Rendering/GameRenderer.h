#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

class Scene;

class GameRenderer
{
public:
	bool Init();
	void Destroy();

	void Render();

	void SetScene(Scene* pScene);

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	Scene* m_pScene;
};
#endif // !GAMERENDERER_H
