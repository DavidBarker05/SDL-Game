#ifndef SCENE_H
#define SCENE_H

#include "Core.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <vector>
#include "Entity.h"
#include "InputManager.h"
#include "Renderable.h"

class Scene : public Renderable
{
public:
	Scene();

	virtual void HandleInput(InputManager* pInputManager);
	virtual void HandleEvent(const SDL_Event& event);
	virtual void Tick(FLOAT32 deltaTime);
	virtual void Render(GameRenderer& gameRenderer) override;

	virtual void AddEntity(Entity* pEntity);

private:
	std::vector<Entity*> m_pEntities;
};
#endif // !SCENE_H
