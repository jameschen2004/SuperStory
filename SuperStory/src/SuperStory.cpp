#include "SuperStory.h"

Map* map;

SDL_Renderer* SuperStory::renderer = nullptr;

Manager manager;
auto& player(manager.addEntity());

SuperStory::SuperStory() {}

SuperStory::~SuperStory() {}

void SuperStory::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SuperStory Launched Successfully\n";
		
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;		

	}

	map = new Map();

	player.addComponent<PositionComponent>();
	player.addComponent<SpriteComponent>("assets/ditto.png");

}

void SuperStory::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void SuperStory::update()
{
	manager.refresh();
	manager.update();
}

void SuperStory::render()
{
	SDL_RenderClear(renderer);
	
	map->DrawMap();

	manager.draw();
	SDL_RenderPresent(renderer);
}
void SuperStory::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned\n";
}

bool SuperStory::running()
{
	return (isRunning);
}