#ifndef GAMERENDERER_H
#define GAMERENDERER_H

class GameRenderer
{
public:
	static bool Init();
	static void Shutdown();

	static void Render();
};
#endif // !GAMERENDERER_H
