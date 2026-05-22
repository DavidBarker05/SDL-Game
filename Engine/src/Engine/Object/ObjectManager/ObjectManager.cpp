#include "ObjectManager.h"
#include "../Object.h"
#include <unordered_set>

static std::unordered_set<Object*> s_Objects;

void ObjectManager::AddObject(Object* pObject)
{
    if (pObject) s_Objects.emplace(pObject);
}

void ObjectManager::RemoveObject(Object* pObject)
{
    if (pObject) s_Objects.erase(pObject);
}

bool ObjectManager::IsObjectValid(Object* pObject)
{
    return pObject && s_Objects.find(pObject) != s_Objects.end();
}
