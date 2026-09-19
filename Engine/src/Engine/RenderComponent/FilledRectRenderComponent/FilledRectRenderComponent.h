#pragma once

#include "../RenderComponent.h"

class FilledRectRenderComponent : public RenderComponent
{
public:
    typedef RenderComponent Super;

    void Draw() override;

    Bounds2D GetBounds() const { return m_Bounds; }
    RenderComponent& SetBounds(Bounds2D bounds)
    {
        m_Bounds = bounds;
        return *this;
    }

    Color GetColor() const { return m_Colour; }
    RenderComponent& SetColor(Color color)
    {
        m_Colour = color;
        return *this;
    }

private:
    Bounds2D m_Bounds;
    Color m_Colour;
};
