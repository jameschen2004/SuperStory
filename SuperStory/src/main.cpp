#include "SuperStory.h"

SuperStory* superstory = nullptr;

int main(int argc, char *argv[])
{

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	superstory = new SuperStory();
	superstory->init("Super Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (superstory->running())
	{
		frameStart = SDL_GetTicks();

		superstory->handleEvents();
		superstory->update();
		superstory->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}

	}

	superstory->clean();

	return 0;
}