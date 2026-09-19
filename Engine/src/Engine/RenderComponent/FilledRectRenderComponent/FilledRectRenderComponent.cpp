#include "FilledRectRenderComponent.h"
#include "Entity/Entity.h"

void FilledRectRenderComponent::Draw()
{
    if (std::shared_ptr<Entity> spOwner = Owner().lock())
        Renderer::DrawFilledRect(m_RenderLayer, spOwner->GetPosition() + m_Bounds.Centre, m_Bounds.HalfExtents,
                                 m_Colour);
}
