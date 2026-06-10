#pragma once

// Why did I do this to myself? I should have just kept it with
// SDL instead of wraping everything

#include "Event.h"
#include "InputCode.h"
#include "Types.h"
#include <typeinfo>

class InputEvent : public Event
{
private:
    // Uses vary basic custom form similar to std::any that lets this work pre c++17
    struct BaseStorage
    {
        virtual ~BaseStorage() { }
        virtual const std::type_info& Type() const = 0;
    };

    template<typename T>
    struct TemplatedStorage : public BaseStorage
    {
        T Value;
        TemplatedStorage(const T& value) : Value(value) { }
        const std::type_info& Type() const override { return typeid(T); }
    };

public:
    template<typename T>
    InputEvent(InputDevice inputDevice, InputType inputType, UINT32 inputCode, const T& value) :
        m_InputDevice(inputDevice), m_InputType(inputType), m_InputCode(inputCode),
        m_pValue(new TemplatedStorage<T>(value))
    {
    }

    ~InputEvent()
    {
        if (m_pValue) delete m_pValue;
    }

    InputDevice GetInputDevice() const { return m_InputDevice; }
    InputType GetInputType() const { return m_InputType; }
    UINT32 GetInputCode() const { return m_InputCode; }
    template<typename T>
    const T* ReadValue() const
    {
        if (!m_pValue || m_pValue->Type() != typeid(T)) return nullptr;
        return &static_cast<TemplatedStorage<T>*>(m_pValue)->Value;
    }

private:
    InputDevice m_InputDevice;
    InputType m_InputType;
    UINT32 m_InputCode;
    BaseStorage* m_pValue;
};
