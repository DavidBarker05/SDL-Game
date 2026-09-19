#include "RenderComponent.h"

void RenderComponent::Destroy() { Renderer::RemoveFromRenderList(Cast<RenderComponent>(shared_from_this())); }
