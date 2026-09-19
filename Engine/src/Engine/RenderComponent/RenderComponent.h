#pragma once

#include "Engine/Component/Component.h" // For some reason I have to specify engine even tho I have it as an include directory?
#include "Renderer/Renderer.h"
#include "Types.h"

class RenderComponent : public Component
{
public:
    typedef Component Super;

public:
    virtual void OnCreate() override;
    virtual void OnDestroy() override;

    virtual void Draw() { };

    UINT32 GetRenderLayer() const { return m_RenderLayer; }
    RenderComponent& SetRenderLayer(UINT32 renderLayer)
    {
        m_RenderLayer = renderLayer;
        return *this;
    }

protected:
    UINT32 m_RenderLayer = 0;
};
