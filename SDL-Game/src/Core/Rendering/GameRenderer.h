#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include "Core.h"
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <vector>
#include <memory>
#include "Renderable.h"

class GameRenderer
{
public:
	bool Init();
	void Destroy();

	void Render();

	bool DoesVectorContainRenderable(std::weak_ptr<Renderable> wpRenderable);
	void AddRenderable(std::weak_ptr<Renderable> wpRenderable);
	void AddRenderableAtIndex(std::weak_ptr<Renderable> wpRenderable, SIZE_T index);
	void RemoveRenderable(std::weak_ptr<Renderable> wpRenderable);

private:
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	std::vector<std::weak_ptr<Renderable>> m_wpRenderables;
};
#endif // !GAMERENDERER_H
