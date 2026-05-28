#include "Events/EventSystem.h"
#include "Input/InputSystem.h"
#include "Logging/Log.h"
#include <SDL3/SDL_init.h>

static SDL_Gamepad* s_pGamePad = nullptr;

bool EventSystem::Init()
{
    if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_GAMEPAD))
    {
        LOG_FATAL("%s", SDL_GetError());
        return false;
    }
    INT32 numGamepads = 0;
    SDL_JoystickID* gamepads = SDL_GetGamepads(&numGamepads);
    if (numGamepads > 0) s_pGamePad = SDL_OpenGamepad(gamepads[0]);
    SDL_free(gamepads);
    LOG_INFO("Initialised the event manager");
    return true;
}

void EventSystem::Shutdown()
{
    if (s_pGamePad) SDL_CloseGamepad(s_pGamePad);
    // Nothing for now but might be needed later
}

UINT32 EventSystem::PollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT) return Quit;
        InputSystem::HandleInput(event);
    }
    return AllEventsPolled;
}
