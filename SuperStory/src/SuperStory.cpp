#include "SuperStory.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

SDL_Renderer* SuperStory::renderer = nullptr;
Map* map;
Manager manager;
SDL_Event SuperStory::event;

std::vector<ColliderComponent*> SuperStory::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

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

	tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
	tile1.addComponent<TileComponent>(250, 250, 32, 32, 1);
	tile1.addComponent<ColliderComponent>("dirt");
	tile2.addComponent<TileComponent>(150, 150, 32, 32, 2);
	tile2.addComponent<ColliderComponent>("grass");

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

	for (auto cc : colliders)
	{
		Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
	}
}

void SuperStory::render()
{
	SDL_RenderClear(renderer);

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