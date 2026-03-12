#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include "Core.h"
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>
#include <vector>
#include <memory>

class Renderable;

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

	void RenderRectangle(Vec2D center, Vec2D halfExtents, UINT8 red, UINT8 green, UINT8 blue, UINT8 alpha);
	void RenderTexture(SDL_Texture* pTexture, Vec2D center, Vec2D halfExtents);

private:
	SDL_GPUDevice* m_pGPUDevice;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	std::vector<std::weak_ptr<Renderable>> m_wpRenderables;
};
#endif // !GAMERENDERER_H
