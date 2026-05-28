#pragma once

#include "../Engine/Object/ObjectManager/ObjectManager.h"

template<typename To, typename From>
inline To* Cast(From* from)
{
    return dynamic_cast<To*>(from);
}

inline bool IsValid(Object* pObject) { return ObjectManager::IsObjectValid(pObject); }
