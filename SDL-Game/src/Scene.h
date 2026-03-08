#ifndef SCENE_H
#define SCENE_H

#include "Core/DataTypes.h"
#include <SDL2/SDL_render.h>
#include <vector>
#include "Entity.h"
#include "Events/InputManager.h"
#include <SDL2/SDL_events.h>

class Scene
{
public:
	Scene();

	virtual void HandleInput(InputManager* pInputManager);
	virtual void HandleEvent(SDL_Event event);
	virtual void Tick(FLOAT32 deltaTime);
	virtual void Render(SDL_Renderer* pRenderer);

	virtual void AddEntity(Entity* pEntity);

private:
	std::vector<Entity*> m_pEntities;
};
#endif // !SCENE_H
