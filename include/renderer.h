#pragma once

#include "blocks.h"
#include <SDL3/SDL.h>
#include <vector>

class Renderer {
public:

	SDL_Renderer* renderer;

	Renderer(SDL_Renderer* renderer);

	void Draw(SDL_Renderer* renderer, std::vector<CombinedBlock>& Blocks, double SimulationScale, double WorldSize[2]);
};