#ifndef SCENE_H
#define SCENE_H

#include "Core.h"
#include <vector>
#include "Entity.h"
#include "InputManager.h"

struct WorldDetails
{
	WORLD_DEF worldDef;
	WORLD_ID worldId;
};

class Scene
{
public:
	Scene();

	virtual void HandleInput(InputManager* pInputManager);
	virtual void HandleEvent(EVENT event);
	virtual void TickPhysics(FLOAT32 fixedDeltaTime);
	virtual void Tick(FLOAT32 deltaTime);
	virtual void Render(P_RENDERER pRenderer);

	virtual void AddEntity(Entity* pEntity);

private:
	std::vector<Entity*> m_pEntities;
	WorldDetails* m_pWorldDetails;
};
#endif // !SCENE_H
