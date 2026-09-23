#pragma once

#include "blocks.h"
#include <SDL3/SDL.h>
#include <vector>
#include <array>

class Renderer {
public:

	SDL_Renderer* renderer;

	Renderer(SDL_Renderer* renderer);

	void Draw(SDL_Renderer* renderer, std::vector<CombinedBlock>& Blocks, double SimulationScale, double WorldSize[2], double WorldOffset[2], bool ShowInteractionLines, std::vector<std::array<double, 2>> Path);
};