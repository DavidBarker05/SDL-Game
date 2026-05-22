#include "FilledRectRenderComponent.h"
#include "../Entity/Entity.h"

FilledRectRenderComponent::FilledRectRenderComponent(Vector2 position, Vector2 halfExtents,
                                                     Color color) :
    Super(), m_CentreOffset(position), m_HalfExtents(halfExtents), m_Colour(color)
{
}

FilledRectRenderComponent::FilledRectRenderComponent(UINT32 renderLayer, Vector2 position,
                                                     Vector2 halfExtents, Color color) :
    Super(renderLayer), m_CentreOffset(position), m_HalfExtents(halfExtents), m_Colour(color)
{
}

void FilledRectRenderComponent::Draw()
{
    Renderer::DrawFilledRect(m_RenderLayer, Owner()->GetPosition() + m_CentreOffset, m_HalfExtents,
                             m_Colour);
}
