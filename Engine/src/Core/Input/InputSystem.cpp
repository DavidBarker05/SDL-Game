#include "InputSystem.h"
#include "Events/GamepadManager.h"
#include "Events/SDLCodeConverter.h"
#include "Logging/Log.h"
#include <SDL3/SDL_events.h>
#include <unordered_map>

static std::unordered_map<KeyCode, bool> s_KeysStarted;
static std::unordered_map<KeyCode, bool> s_KeysHeld;
static std::unordered_map<KeyCode, bool> s_KeysReleased;

static std::unordered_map<GamepadCode, bool> s_GamepadControlsStarted;
static std::unordered_map<GamepadCode, bool> s_GamepadControlsHeld;
static std::unordered_map<GamepadCode, bool> s_GamepadControlsReleased;

void InputSystem::HandleInput(const InputEvent& inputEvent)
{
    switch (inputEvent.GetInputDevice())
    {
        case InputDevice::eDEVICE_KEYBOARD:
            if (inputEvent.GetInputType() == InputType::eTYPE_STARTED)
            {
                s_KeysStarted[(KeyCode)inputEvent.GetInputCode()] = true;
                s_KeysReleased[(KeyCode)inputEvent.GetInputCode()] = false;
            }
            else if (inputEvent.GetInputType() == InputType::eTYPE_RELEASED)
            {
                s_KeysStarted[(KeyCode)inputEvent.GetInputCode()] = false;
                s_KeysReleased[(KeyCode)inputEvent.GetInputCode()] = true;
            }
            break;
        case InputDevice::eDEVICE_GAMEPAD:
            if (inputEvent.GetInputType() == InputType::eTYPE_STARTED)
            {
                s_GamepadControlsStarted[(GamepadCode)inputEvent.GetInputCode()] = true;
                s_GamepadControlsReleased[(GamepadCode)inputEvent.GetInputCode()] = false;
            }
            else if (inputEvent.GetInputType() == InputType::eTYPE_RELEASED)
            {
                s_GamepadControlsStarted[(GamepadCode)inputEvent.GetInputCode()] = false;
                s_GamepadControlsReleased[(GamepadCode)inputEvent.GetInputCode()] = true;
            }
            break;
        default:
            break;
    }
    // switch (event.type)
    //{
    //     case SDL_EVENT_KEY_DOWN:
    //         LOG_INFO("%d", event.key.repeat);
    //         DoKeyDown(event.key.key);
    //         break;
    //     case SDL_EVENT_KEY_UP:
    //         DoKeyUp(event.key.key);
    //         break;
    //     case SDL_EVENT_GAMEPAD_AXIS_MOTION:
    //         // LOG_INFO("Gamepad motion detected: %.3f", event.gaxis.value / 32767.0f);
    //         break;
    //     case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
    //         LOG_INFO("Gamepad button pressed");
    //         break;
    //     default:
    //         break;
    // }
}

static void UpdateKeyStateValue(KeyCode keyCode, bool bIsHeld)
{
    if (s_KeysStarted[keyCode] && s_KeysHeld[keyCode])
        s_KeysStarted[keyCode] = false; // Started last poll so stop being started
    if (!s_KeysHeld[keyCode] && s_KeysReleased[keyCode])
        s_KeysReleased[keyCode] = false; // Released last poll so stop being released
    s_KeysHeld[keyCode] = bIsHeld;
}

static void UpdateKeyboardStateValues()
{
    const bool* keys = SDL_GetKeyboardState(nullptr);
    for (int i = 0; i < SDL_SCANCODE_COUNT; ++i)
    {
        UpdateKeyStateValue(ConvertFromSDLScancode((SDL_Scancode)i), keys[i]);
    }
    UpdateKeyStateValue(KeyCode::eENTER_ANY,
                        s_KeysHeld[KeyCode::eENTER] || s_KeysHeld[KeyCode::eKEYPAD_ENTER]);
}

static void UpdateGamepadButtonStateValue(GamepadCode buttonCode)
{
    if (s_GamepadControlsStarted[buttonCode] && s_GamepadControlsHeld[buttonCode])
        s_GamepadControlsStarted[buttonCode] = false; // Started last poll so stop being started
    if (!s_GamepadControlsHeld[buttonCode] && s_GamepadControlsReleased[buttonCode])
        s_GamepadControlsReleased[buttonCode] = false; // Released last poll so stop being released
    s_GamepadControlsHeld[buttonCode] = SDL_GetGamepadButton(GamepadManager::CurrentGamepad(),
                                                             ConvertToSDLGamepadButton(buttonCode));
}

static void UpdateGamepadButtonStateValues()
{
    for (UINT32 i = (UINT32)GamepadCode::eUNKNOWN + 1; i < (UINT32)GamepadCode::COUNT; ++i)
        UpdateGamepadButtonStateValue((GamepadCode)i);
}

static void UpdateGamepadStateValues()
{
    if (!GamepadManager::CurrentGamepad()) return;
    UpdateGamepadButtonStateValues();
}

void InputSystem::UpdateInputStateValues()
{
    UpdateKeyboardStateValues();
    UpdateGamepadStateValues();
}

bool InputSystem::IsControlStarted(InputDevice inputDevice, UINT32 inputCode)
{
    switch (inputDevice)
    {
        case InputDevice::eDEVICE_GAMEPAD:
            if (inputCode >= (UINT32)GamepadCode::COUNT) return false;
            return IsControlStarted((GamepadCode)inputCode);
        default:
            return false;
    }
}

bool InputSystem::IsControlStarted(KeyCode keyCode) { return s_KeysStarted[keyCode]; }

bool InputSystem::IsControlStarted(GamepadCode gamepadCode)
{
    return s_GamepadControlsStarted[gamepadCode];
}

Vec2D InputSystem::GetMoveInput()
{
    bool up = s_KeysHeld[KeyCode::eW] || s_KeysHeld[KeyCode::eUP] ||
              s_GamepadControlsHeld[GamepadCode::eDPAD_UP];
    bool down = s_KeysHeld[KeyCode::eS] || s_KeysHeld[KeyCode::eDOWN] ||
                s_GamepadControlsHeld[GamepadCode::eDPAD_DOWN];
    bool right = s_KeysHeld[KeyCode::eD] || s_KeysHeld[KeyCode::eRIGHT] ||
                 s_GamepadControlsHeld[GamepadCode::eDPAD_RIGHT];
    bool left = s_KeysHeld[KeyCode::eA] || s_KeysHeld[KeyCode::eLEFT] ||
                s_GamepadControlsHeld[GamepadCode::eDPAD_LEFT];
    FLOAT32 y = up && !down ? -1.0f : (down && !up ? 1.0f : 0.0f);
    FLOAT32 x = right && !left ? 1.0f : (left && !right ? -1.0f : 0.0f);
    return Vec2D(x, y);
}
