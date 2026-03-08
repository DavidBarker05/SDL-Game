#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

class Player;

class GameRenderer
{
public:
	bool Init();
	void Destroy();

	void Render();

	void SetPlayer(Player* pPlayer);

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	Player* m_pPlayer;
};
#endif // !GAMERENDERER_H
