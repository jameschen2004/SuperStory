#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "ECS.h"
#include "Components.h"

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class SuperStory {
public: 
	SuperStory();
	~SuperStory();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running();

	static SDL_Renderer* renderer;

private: 
	bool isRunning;
	SDL_Window* window;
	int cnt = 0;
};