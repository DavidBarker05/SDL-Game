#include "Events/EventSystem.h"
#include "Event.h"
#include "GamepadManager.h"
#include "Input/InputSystem.h"
#include "InputEvent.h"
#include "Logging/Log.h"
#include "SDLCodeConverter.h"
#include <SDL3/SDL_init.h>

bool EventSystem::Init()
{
    if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_GAMEPAD))
    {
        LOG_FATAL("%s", SDL_GetError());
        return false;
    }
    GamepadManager::Init();
    LOG_INFO("Initialised the event manager");
    return true;
}

void EventSystem::Shutdown() { GamepadManager::Shutdown(); }

static InputEvent* CreateInputEvent(const SDL_Event& event)
{
    InputDevice inputDevice;
    InputType inputType;
    UINT32 inputCode;
    FLOAT32 valueFloat;
    INT32 valueInt;
    Vector2 valueVector;
    InputEvent* pInputEvent = nullptr;
    if ((event.type == SDL_EVENT_KEY_DOWN && !event.key.repeat) || event.type == SDL_EVENT_KEY_UP)
    {
        inputDevice = InputDevice::eDEVICE_KEYBOARD;
        inputType =
            event.type == SDL_EVENT_KEY_DOWN ? InputType::eTYPE_STARTED : InputType::eTYPE_RELEASED;
        inputCode = (UINT32)ConvertFromSDLKeyEvent(event.key);
        pInputEvent = new InputEvent(inputDevice, inputType, inputCode, (void*)nullptr);
    }
    else if (event.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN ||
             event.type == SDL_EVENT_GAMEPAD_BUTTON_UP)
    {
        inputDevice = InputDevice::eDEVICE_GAMEPAD;
        inputType = event.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN ? InputType::eTYPE_STARTED :
                                                                  InputType::eTYPE_RELEASED;
        inputCode = (UINT32)ConvertFromSDLGamepadButtonEvent(event.gbutton);
        pInputEvent = new InputEvent(inputDevice, inputType, inputCode, (void*)nullptr);
    }
    return pInputEvent;
}

static Event* ConvertSDLEvent(const SDL_Event& event)
{
    Event* pEvent = nullptr;
    if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP ||
        event.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN || event.type == SDL_EVENT_GAMEPAD_BUTTON_UP)
        pEvent = CreateInputEvent(event);
    return pEvent;
}

UINT32 EventSystem::PollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_EVENT_QUIT) return Quit;
        if (Event* pEvent = ConvertSDLEvent(event))
        {
            if (InputEvent* pInputEvent = dynamic_cast<InputEvent*>(pEvent))
                InputSystem::HandleInput(*pInputEvent);
            delete pEvent;
        }
        InputSystem::UpdateInputStateValues();
    }
    return AllEventsPolled;
}
