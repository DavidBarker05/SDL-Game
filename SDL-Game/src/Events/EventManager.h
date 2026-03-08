#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "Core.h"
#include "InputManager.h"

class Scene;

enum class PollStatus : UINT8
{
	eALL_EVENTS_POLLED,
	eQUIT
};

class EventManager
{
public:
	bool Init();

	PollStatus PollEvents();

	InputManager& GetInputManager();

	void SetScene(Scene* pScene);

private:
	InputManager m_InputManager;

	Scene* m_pScene;
};
#endif // !EVENTMANAGER_H
