#pragma once

#include "InputEvent.h"
#include <SDL3/SDL_events.h>

inline KeyCode ConvertFromSDLScancode(SDL_Scancode scancode)
{
    switch (scancode)
    {
        case SDL_SCANCODE_A:
            return KeyCode::eA;
        case SDL_SCANCODE_B:
            return KeyCode::eB;
        case SDL_SCANCODE_C:
            return KeyCode::eC;
        case SDL_SCANCODE_D:
            return KeyCode::eD;
        case SDL_SCANCODE_E:
            return KeyCode::eE;
        case SDL_SCANCODE_F:
            return KeyCode::eF;
        case SDL_SCANCODE_G:
            return KeyCode::eG;
        case SDL_SCANCODE_H:
            return KeyCode::eH;
        case SDL_SCANCODE_I:
            return KeyCode::eI;
        case SDL_SCANCODE_J:
            return KeyCode::eJ;
        case SDL_SCANCODE_K:
            return KeyCode::eK;
        case SDL_SCANCODE_L:
            return KeyCode::eL;
        case SDL_SCANCODE_M:
            return KeyCode::eM;
        case SDL_SCANCODE_N:
            return KeyCode::eN;
        case SDL_SCANCODE_O:
            return KeyCode::eO;
        case SDL_SCANCODE_P:
            return KeyCode::eP;
        case SDL_SCANCODE_Q:
            return KeyCode::eQ;
        case SDL_SCANCODE_R:
            return KeyCode::eR;
        case SDL_SCANCODE_S:
            return KeyCode::eS;
        case SDL_SCANCODE_T:
            return KeyCode::eT;
        case SDL_SCANCODE_U:
            return KeyCode::eU;
        case SDL_SCANCODE_V:
            return KeyCode::eV;
        case SDL_SCANCODE_W:
            return KeyCode::eW;
        case SDL_SCANCODE_X:
            return KeyCode::eX;
        case SDL_SCANCODE_Y:
            return KeyCode::eY;
        case SDL_SCANCODE_Z:
            return KeyCode::eZ;
        default:
            return KeyCode::eUNKNOWN;
    }
}

inline KeyCode ConvertFromSDLKeyEvent(const SDL_KeyboardEvent& keyboardEvent)
{
    return ConvertFromSDLScancode(keyboardEvent.scancode);
}

inline GamepadCode ConvertFromSDLGamepadButton(SDL_GamepadButton button)
{
    switch (button)
    {
        case SDL_GAMEPAD_BUTTON_SOUTH:
            return GamepadCode::eBUTTON_SOUTH;
        case SDL_GAMEPAD_BUTTON_EAST:
            return GamepadCode::eBUTTON_EAST;
        case SDL_GAMEPAD_BUTTON_WEST:
            return GamepadCode::eBUTTON_WEST;
        case SDL_GAMEPAD_BUTTON_NORTH:
            return GamepadCode::eBUTTON_NORTH;
        case SDL_GAMEPAD_BUTTON_BACK:
            return GamepadCode::eBACK;
        case SDL_GAMEPAD_BUTTON_GUIDE:
            return GamepadCode::eGUIDE;
        case SDL_GAMEPAD_BUTTON_START:
            return GamepadCode::eSTART;
        case SDL_GAMEPAD_BUTTON_LEFT_STICK:
            return GamepadCode::eLEFT_STICK_PRESS;
        case SDL_GAMEPAD_BUTTON_RIGHT_STICK:
            return GamepadCode::eRIGHT_STICK_PRESS;
        case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER:
            return GamepadCode::eLEFT_SHOULDER;
        case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER:
            return GamepadCode::eRIGHT_SHOULDER;
        case SDL_GAMEPAD_BUTTON_DPAD_UP:
            return GamepadCode::eDPAD_UP;
        case SDL_GAMEPAD_BUTTON_DPAD_DOWN:
            return GamepadCode::eDPAD_DOWN;
        case SDL_GAMEPAD_BUTTON_DPAD_LEFT:
            return GamepadCode::eDPAD_LEFT;
        case SDL_GAMEPAD_BUTTON_DPAD_RIGHT:
            return GamepadCode::eDPAD_RIGHT;
        case SDL_GAMEPAD_BUTTON_MISC1:
            return GamepadCode::eBUTTON_MISC1;
        case SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1:
            return GamepadCode::eRIGHT_PADDLE1;
        case SDL_GAMEPAD_BUTTON_LEFT_PADDLE1:
            return GamepadCode::eLEFT_PADDLE1;
        case SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2:
            return GamepadCode::eRIGHT_PADDLE2;
        case SDL_GAMEPAD_BUTTON_LEFT_PADDLE2:
            return GamepadCode::eLEFT_PADDLE2;
        case SDL_GAMEPAD_BUTTON_TOUCHPAD:
            return GamepadCode::eTOUCHPAD_PRESS;
        case SDL_GAMEPAD_BUTTON_MISC2:
            return GamepadCode::eBUTTON_MISC2;
        case SDL_GAMEPAD_BUTTON_MISC3:
            return GamepadCode::eBUTTON_MISC3;
        case SDL_GAMEPAD_BUTTON_MISC4:
            return GamepadCode::eBUTTON_MISC4;
        case SDL_GAMEPAD_BUTTON_MISC5:
            return GamepadCode::eBUTTON_MISC5;
        case SDL_GAMEPAD_BUTTON_MISC6:
            return GamepadCode::eBUTTON_MISC6;
        default:
            return GamepadCode::eUNKNOWN;
    }
}

inline SDL_GamepadButton ConvertToSDLGamepadButton(GamepadCode gamepadCode)
{
    switch (gamepadCode)
    {
        case GamepadCode::eBUTTON_SOUTH:
            return SDL_GAMEPAD_BUTTON_SOUTH;
        case GamepadCode::eBUTTON_EAST:
            return SDL_GAMEPAD_BUTTON_EAST;
        case GamepadCode::eBUTTON_WEST:
            return SDL_GAMEPAD_BUTTON_WEST;
        case GamepadCode::eBUTTON_NORTH:
            return SDL_GAMEPAD_BUTTON_NORTH;
        case GamepadCode::eBACK:
            return SDL_GAMEPAD_BUTTON_BACK;
        case GamepadCode::eGUIDE:
            return SDL_GAMEPAD_BUTTON_GUIDE;
        case GamepadCode::eSTART:
            return SDL_GAMEPAD_BUTTON_START;
        case GamepadCode::eLEFT_STICK_PRESS:
            return SDL_GAMEPAD_BUTTON_LEFT_STICK;
        case GamepadCode::eRIGHT_STICK_PRESS:
            return SDL_GAMEPAD_BUTTON_RIGHT_STICK;
        case GamepadCode::eLEFT_SHOULDER:
            return SDL_GAMEPAD_BUTTON_LEFT_SHOULDER;
        case GamepadCode::eRIGHT_SHOULDER:
            return SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER;
        case GamepadCode::eDPAD_UP:
            return SDL_GAMEPAD_BUTTON_DPAD_UP;
        case GamepadCode::eDPAD_DOWN:
            return SDL_GAMEPAD_BUTTON_DPAD_DOWN;
        case GamepadCode::eDPAD_LEFT:
            return SDL_GAMEPAD_BUTTON_DPAD_LEFT;
        case GamepadCode::eDPAD_RIGHT:
            return SDL_GAMEPAD_BUTTON_DPAD_RIGHT;
        case GamepadCode::eTOUCHPAD_PRESS:
            return SDL_GAMEPAD_BUTTON_TOUCHPAD;
        case GamepadCode::eBUTTON_MISC1:
            return SDL_GAMEPAD_BUTTON_MISC1;
        case GamepadCode::eBUTTON_MISC2:
            return SDL_GAMEPAD_BUTTON_MISC2;
        case GamepadCode::eBUTTON_MISC3:
            return SDL_GAMEPAD_BUTTON_MISC3;
        case GamepadCode::eBUTTON_MISC4:
            return SDL_GAMEPAD_BUTTON_MISC4;
        case GamepadCode::eBUTTON_MISC5:
            return SDL_GAMEPAD_BUTTON_MISC5;
        case GamepadCode::eBUTTON_MISC6:
            return SDL_GAMEPAD_BUTTON_MISC6;
        case GamepadCode::eRIGHT_PADDLE1:
            return SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1;
        case GamepadCode::eRIGHT_PADDLE2:
            return SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2;
        case GamepadCode::eLEFT_PADDLE1:
            return SDL_GAMEPAD_BUTTON_LEFT_PADDLE1;
        case GamepadCode::eLEFT_PADDLE2:
            return SDL_GAMEPAD_BUTTON_LEFT_PADDLE2;
        default:
            return SDL_GAMEPAD_BUTTON_INVALID;
    }
}

inline GamepadCode
ConvertFromSDLGamepadButtonEvent(const SDL_GamepadButtonEvent& gamepadButtonEvent)
{
    return ConvertFromSDLGamepadButton((SDL_GamepadButton)gamepadButtonEvent.button);
}
