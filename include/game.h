#pragma once
#include <SDL3/SDL.h>
#include "window.h"
#include "renderer.h"
#include "blocks.h"
#include "physics.h"
#include <vector>

class Game {
public:
	Game();

	void run();

private:
	Window window;
	Renderer renderer;
	bool running;
	SDL_Event e;
	const double GravitationalConstant;
	std::vector<CombinedBlock> Blocks;
	Physics physics;
	BlocksManager blocksManager;
	double dt;
	double MetersPerPixel;
	double SimulationScale;
	SDL_FRect mouse;
};