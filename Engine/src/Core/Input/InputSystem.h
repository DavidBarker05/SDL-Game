#pragma once

#include "Events/InputEvent.h"
#include "Math/Vector2D.h"

class InputSystem
{
public:
    static void HandleInput(const InputEvent& inputEvent);

    static void UpdateInputStateValues();

    static bool IsControlStarted(InputDevice inputDevice, UINT32 inputCode);
    static bool IsControlStarted(KeyCode keyCode);
    static bool IsControlStarted(GamepadCode gamepadCode);

    static Vector2 GetMoveInput();
};
