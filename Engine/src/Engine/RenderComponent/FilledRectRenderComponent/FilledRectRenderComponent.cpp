#include "FilledRectRenderComponent.h"
#include "Entity/Entity.h"

void FilledRectRenderComponent::Draw()
{
    Renderer::DrawFilledRect(m_RenderLayer, Owner()->GetPosition() + m_Bounds.Centre, m_Bounds.HalfExtents, m_Colour);
}
