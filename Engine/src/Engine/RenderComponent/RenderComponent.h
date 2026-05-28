#pragma once

#include "Engine/Component/Component.h" // For some reason I have to specify engine even tho I have it as an include directory?
#include "Renderer/Renderer.h"
#include "Types.h"

class RenderComponent : public Component
{
public:
    typedef Component Super;

public:
    virtual void Draw() { };

public:
    UINT32 GetRenderLayer();
    void SetRenderLayer(UINT32 renderLayer);

protected:
    RenderComponent();
    RenderComponent(UINT32 renderLayer);

    virtual ~RenderComponent();

protected:
    UINT32 m_RenderLayer;
};
