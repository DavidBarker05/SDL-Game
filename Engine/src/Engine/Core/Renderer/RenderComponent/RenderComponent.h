#pragma once

#include "../Renderer.h"
#include "Types.h"

class RenderComponent
{
public:
    virtual void Draw() { };

public:
    UINT32 GetRenderLayer();
    void SetRenderLayer(UINT32 renderLayer);

protected:
    RenderComponent(Vector2 const* ownerPosition);
    RenderComponent(UINT32 renderLayer, Vector2 const* ownerPosition);

    virtual ~RenderComponent();

protected:
    UINT32 m_RenderLayer;
    Vector2 const* m_OwnerPosition;
};
