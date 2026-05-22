#include "Object.h"
#include "ObjectManager/ObjectManager.h"

Object::Object() { ObjectManager::AddObject(this); }

Object::~Object() { ObjectManager::RemoveObject(this); }
