#include "window.h"
#include <SDL3/SDL.h>

Window::Window() {
	SDL_CreateWindowAndRenderer("Nbody Newtonian Gravity Sim", WindowWidth, WindowHeight, SDL_WINDOW_RESIZABLE, &window, &renderer);
}

Window::~Window() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}
