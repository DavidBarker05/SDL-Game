#ifndef SCENE_H
#define SCENE_H

#include "Core.h"
#include "Entity.h"
#include <vector>

class Scene
{
public:
    Scene();

    // virtual void HandleEvent(const SDL_Event& event);
    virtual void Tick(FLOAT32 deltaTime);

    virtual void AddEntity(Entity* pEntity);

private:
    std::vector<Entity*> m_pEntities;
};
#endif // !SCENE_H
