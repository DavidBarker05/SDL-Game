#pragma once

// Why did I do this to myself? I should have just kept it with
// SDL instead of wraping everything

#include "Event.h"
#include "InputCode.h"
#include "Types.h"
#include <any>
#include <typeinfo>

class InputEvent : public Event
{
public:
    template<typename T>
    InputEvent(InputDevice inputDevice, InputType inputType, UINT32 inputCode, const T& value) :
        m_InputDevice(inputDevice), m_InputType(inputType), m_InputCode(inputCode), m_Value(value)
    {
    }

    InputDevice GetInputDevice() const { return m_InputDevice; }
    InputType GetInputType() const { return m_InputType; }
    UINT32 GetInputCode() const { return m_InputCode; }
    template<typename T>
    const T* ReadValue() const
    {
        if (!m_Value.has_value() || m_Value.type() != typeid(T)) return nullptr;
        return std::any_cast<T>(m_Value);
    }

private:
    InputDevice m_InputDevice;
    InputType m_InputType;
    UINT32 m_InputCode;
    std::any m_Value;
};
