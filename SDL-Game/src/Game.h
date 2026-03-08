#ifndef GAME_H
#define GAME_H

#include "DataTypes.h"
#include <memory>

class GameRenderer;
class EventManager;

class Game
{
public:
	Game();
	~Game();

	void Init();
	void Start();

	GameRenderer* GetGameRenderer();
	EventManager* GetEventManager();

private:
	void Tick();
	void UpdateDeltaTime();

	bool m_bGameIsRunning;
	FLOAT64 m_DeltaTime;

	std::unique_ptr<GameRenderer> m_upGameRenderer;
	std::unique_ptr<EventManager> m_upEventManager;
};
#endif // !GAME_H
