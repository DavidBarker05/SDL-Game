#include "FilledRectRenderComponent.h"
#include "../Entity/Entity.h"

FilledRectRenderComponent::FilledRectRenderComponent(const Bounds2D& bounds, Color color) :
    Super(), m_Bounds(bounds), m_Colour(color)
{
}

FilledRectRenderComponent::FilledRectRenderComponent(UINT32 renderLayer, const Bounds2D& bounds,
                                                     Color color) :
    Super(renderLayer), m_Bounds(bounds), m_Colour(color)
{
}

void FilledRectRenderComponent::Draw()
{
    Renderer::DrawFilledRect(m_RenderLayer, Owner()->GetPosition() + m_Bounds.Centre,
                             m_Bounds.HalfExtents, m_Colour);
}
