#include "RenderComponent.h"

UINT32 RenderComponent::GetRenderLayer() { return m_RenderLayer; }

void RenderComponent::SetRenderLayer(UINT32 renderLayer) { m_RenderLayer = renderLayer; }

RenderComponent::RenderComponent(Vector2 const* ownerPosition) :
    m_RenderLayer(0), m_OwnerPosition(ownerPosition)
{
    Renderer::AddToRenderList(this);
}

RenderComponent::RenderComponent(UINT32 renderLayer, Vector2 const* ownerPosition) :
    m_RenderLayer(renderLayer), m_OwnerPosition(ownerPosition)
{
    Renderer::RemoveFromRenderList(this);
}

RenderComponent::~RenderComponent() { }
