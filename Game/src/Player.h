#ifndef PLAYER_H
#define PLAYER_H

#include "Core.h"
#include "Game/Entity.h"
#include "Renderer/RenderComponent/FilledRectRenderComponent.h"
#include <SDL3/SDL_render.h>

class Game;

class Player : public Entity
{
public:
    typedef Entity Super;

    Player();

    virtual void Tick(FLOAT32 deltaTime) override;

private:
    Vector2 m_Velocity;
    FilledRectRenderComponent m_RenderComponent;
};
#endif // !PLAYER_H
