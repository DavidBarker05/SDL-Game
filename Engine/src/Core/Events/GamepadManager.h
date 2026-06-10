#pragma once

#include <SDL3/SDL_events.h>

class GamepadManager
{
public:
    static void Init();
    static void Shutdown();

public:
    static SDL_Gamepad* CurrentGamepad();
};
