#include "FilledRectRenderComponent.h"

FilledRectRenderComponent::FilledRectRenderComponent(Vector2 const* ownerPosition, Vector2 position,
                                                     Vector2 halfExtents, Color color) :
    RenderComponent(ownerPosition), m_CentreOffset(position), m_HalfExtents(halfExtents),
    m_Colour(color)
{
}

FilledRectRenderComponent::FilledRectRenderComponent(UINT32 renderLayer,
                                                     Vector2 const* ownerPosition, Vector2 position,
                                                     Vector2 halfExtents, Color color) :
    RenderComponent(renderLayer, ownerPosition), m_CentreOffset(position),
    m_HalfExtents(halfExtents), m_Colour(color)
{
}

void FilledRectRenderComponent::Draw()
{
    Renderer::DrawFilledRect(m_RenderLayer, *m_OwnerPosition + m_CentreOffset, m_HalfExtents,
                             m_Colour);
}
