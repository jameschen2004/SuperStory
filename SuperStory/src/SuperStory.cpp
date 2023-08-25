#include "SuperStory.h"

GameObject* player;
GameObject* enemy;

Map* map;

SDL_Renderer* SuperStory::renderer = nullptr;

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

	player = new GameObject("assets/ditto.png", 0, 0);
	enemy = new GameObject("assets/mimikyu.png", 50, 50);

	map = new Map();

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
	player->Update();
	enemy->Update();
}

void SuperStory::render()
{
	SDL_RenderClear(renderer);
	
	map->DrawMap();

	player->Render();
	enemy->Render();
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