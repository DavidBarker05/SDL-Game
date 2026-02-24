#include <SDL.h>

// SDL forces me to write main like this for some reason
int main(int argc, char** argv)
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event e;
	SDL_Init(SDL_INIT_EVERYTHING);
	bool running = true;

	SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);

	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) running = false;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawPoint(renderer, 640 / 2, 480 / 2);

		SDL_RenderPresent(renderer);
	}

	return 0;
}