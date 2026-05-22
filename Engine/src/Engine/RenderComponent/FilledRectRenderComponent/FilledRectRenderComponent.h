#pragma once

#include "../RenderComponent.h"

class FilledRectRenderComponent : public RenderComponent
{
public:
    typedef RenderComponent Super;

public:
    FilledRectRenderComponent(Vector2 centerOffset, Vector2 halfExtents, Color color);
    FilledRectRenderComponent(UINT32 renderLayer, Vector2 centerOffset, Vector2 halfExtents,
                              Color color);

public:
    void Draw() override;

private:
    Vector2 m_CentreOffset;
    Vector2 m_HalfExtents;
    Color m_Colour;
};
