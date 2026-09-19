#pragma once

#include <memory>

template<typename To, typename From>
To* Cast(From* pFrom)
{
    return dynamic_cast<To*>(pFrom);
}

template<typename To, typename From>
std::shared_ptr<To> Cast(std::shared_ptr<From> spFrom)
{
    return std::static_pointer_cast<To>(spFrom);
}
