#include "RenderComponent.h"

UINT32 RenderComponent::GetRenderLayer() { return m_RenderLayer; }

void RenderComponent::SetRenderLayer(UINT32 renderLayer) { m_RenderLayer = renderLayer; }

RenderComponent::RenderComponent() : m_RenderLayer(0) { Renderer::AddToRenderList(this); }

RenderComponent::RenderComponent(UINT32 renderLayer) : m_RenderLayer(renderLayer)
{
    Renderer::AddToRenderList(this);
}

RenderComponent::~RenderComponent() { Renderer::RemoveFromRenderList(this); }
