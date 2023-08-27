#pragma once

#include "SDL.h"
#include "SDL_image.h"

#include <iostream>



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
	static SDL_Event event;

private: 
	bool isRunning;
	SDL_Window* window;
	int cnt = 0;
};