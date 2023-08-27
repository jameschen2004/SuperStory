#include "SuperStory.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;

SDL_Renderer* SuperStory::renderer = nullptr;

Manager manager;

auto& player(manager.addEntity());

auto& wall(manager.addEntity());

SDL_Event SuperStory::event;

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

	player.addComponent<TransformComponent>(5);
	player.addComponent<SpriteComponent>("assets/ditto.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/grass.png");
	wall.addComponent<ColliderComponent>("wall");
}

void SuperStory::handleEvents()
{
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

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider))
	{
		player.getComponent<TransformComponent>().scale = 2;
		player.getComponent<TransformComponent>().velocity * -1;
		std::cout << "Wall Hit!\n";
	}
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