#pragma once

#include "Color.h"
#include "Math/Bounds2D.h"
#include "Math/Vector2D.h"
#include "Types.h"

class RenderComponent;

class Renderer
{
public:
    static bool Init(CSTRING title, UINT32 windowWidth, UINT32 windowHeight);
    static bool Init();
    static void Shutdown();

public:
    static void AddToRenderList(RenderComponent* renderComponent);
    static void RemoveFromRenderList(RenderComponent* renderComponent);

public:
    static void DrawRect(UINT32 drawLayer, const Vector2& position, const Vector2& halfExtents,
                         Color color);
    static void DrawFilledRect(UINT32 drawLayer, const Vector2& position,
                               const Vector2& halfExtents, Color color);

public:
    static void Render();
};
