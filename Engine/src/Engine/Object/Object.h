#pragma once

#include "Core.h"

class Object : public std::enable_shared_from_this<Object>
{
    friend class ObjectSystem;

protected:
    virtual void OnDestroy() { }
};

class ObjectSystem
{
public:
    template<typename T, std::enable_if_t<std::is_base_of_v<Object, T>, int> = 0>
    static std::shared_ptr<T> Create()
    {
        return std::make_shared<T>();
    }

    template<typename T, std::enable_if_t<std::is_base_of_v<Object, T>, int> = 0>
    static void Destroy(std::shared_ptr<T> spObject)
    {
        if (spObject) spObject->OnDestroy();
    }
};
