#pragma once

#include "../RenderComponent.h"

class FilledRectRenderComponent : public RenderComponent
{
public:
    typedef RenderComponent Super;

public:
    FilledRectRenderComponent(const Bounds2D& bounds, Color color);
    FilledRectRenderComponent(UINT32 renderLayer, const Bounds2D& bounds, Color color);

public:
    void Draw() override;

private:
    Bounds2D m_Bounds;
    Color m_Colour;
};
