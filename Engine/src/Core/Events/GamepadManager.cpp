#include "GamepadManager.h"
#include "Logging/Log.h"
#include "Types.h"

static SDL_Gamepad* s_pGamepad = nullptr;

void GamepadManager::Init()
{
    LOG_INFO("Gamepad system initialising");
    INT32 numGamepads = 0;
    SDL_JoystickID* gamepads = SDL_GetGamepads(&numGamepads);
    if (numGamepads > 0)
    {
        LOG_INFO(
            "%d gamepad(s) connected to the current device using the first one detected by SDL",
            numGamepads);
        s_pGamepad = SDL_OpenGamepad(gamepads[0]);
    }
    else LOG_INFO("No detected gamepads currently connected to the device");
    SDL_free(gamepads);
    LOG_INFO("Gamepad system initialised");
}

void GamepadManager::Shutdown()
{
    if (s_pGamepad) SDL_CloseGamepad(s_pGamepad);
}

SDL_Gamepad* GamepadManager::CurrentGamepad() { return s_pGamepad; }
