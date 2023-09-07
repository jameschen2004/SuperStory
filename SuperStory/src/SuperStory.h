#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include <iostream>
#include <vector>

class AssetManager;
class ColliderComponent;

class SuperStory {
public: 
	SuperStory();
	~SuperStory();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static SDL_Rect camera;

	static bool isRunning;
	static AssetManager* assets;

	enum groupLabels : std::size_t
	{
		groupMaps,
		groupPlayers,
		groupColliders,
		groupProjectiles
	};

private: 

	SDL_Window* window;
	int cnt = 0;
};