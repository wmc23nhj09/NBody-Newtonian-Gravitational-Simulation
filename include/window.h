#pragma once
#include <SDL3/SDL.h>

class Window {
public:
	int WindowWidth = 1980;
	int WindowHeight = 1080;

	Window();

	~Window();

	SDL_Window* window;
	SDL_Renderer* renderer;
};