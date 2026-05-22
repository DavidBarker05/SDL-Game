#pragma once

class Object;

class ObjectManager
{
public:
    static void AddObject(Object* pObject);
    static void RemoveObject(Object* pObject);

public:
    static bool IsObjectValid(Object* pObject);
};
