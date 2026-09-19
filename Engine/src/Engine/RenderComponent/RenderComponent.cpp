#include "RenderComponent.h"

void RenderComponent::OnCreate()
{
    Renderer::AddToRenderList(std::static_pointer_cast<RenderComponent>(shared_from_this()));
}

void RenderComponent::OnDestroy() { Renderer::RemoveFromRenderList(Cast<RenderComponent>(shared_from_this())); }
