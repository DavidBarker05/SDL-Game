#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL2/SDL_stdinc.h>

enum class PollStatus : Uint8
{
	ALL_EVENTS_POLLED,
	QUIT
};

class InputManager
{
public:
	void Init();

	PollStatus PollEvents();

private:
	
	void DoKeyDown(Uint32 keyCode);
	void DoKeyUp(Uint32 keyCode);
};
#endif // !INPUTMANAGER_H
