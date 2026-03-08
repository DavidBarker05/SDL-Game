#ifndef GAMERENDERER_H
#define GAMERENDERER_H

#include "Core.h"

class Scene;

class GameRenderer
{
public:
	bool Init();
	void Destroy();

	void Render();

	void SetScene(Scene* pScene);

private:
	P_WINDOW m_pWindow;
	P_RENDERER m_pRenderer;

	Scene* m_pScene;
};
#endif // !GAMERENDERER_H
