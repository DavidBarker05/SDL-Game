#ifndef SCENE_H
#define SCENE_H

#include "Core.h"
#include <SDL3/SDL_render.h>
#include <vector>
#include "Entity.h"
#include "Core/Rendering/Renderable.h"

class Scene : public Renderable
{
public:
	Scene();

	//virtual void HandleEvent(const SDL_Event& event);
	virtual void Tick(FLOAT32 deltaTime);
	virtual void Render(SDL_Renderer* pRenderer) override;

	virtual void AddEntity(Entity* pEntity);

private:
	std::vector<Entity*> m_pEntities;
};
#endif // !SCENE_H
