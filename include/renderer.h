#pragma once

#include "blocks.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <vector>
#include <array>

class Renderer {
public:

	SDL_Renderer* renderer;

	Renderer(SDL_Renderer* renderer);

	void Draw(SDL_Renderer* renderer, std::vector<CombinedBlock>& Blocks, double SimulationScale, double MetersPerPixel, double WorldSize[2], double WorldOffset[2], bool ShowInteractionLines, bool ShowAllOrbitLines, std::vector<std::array<double, 2>> Path, bool CreationTable, int* SelectedBlock, double SimTime, bool hoveringOver);
	void DrawGrid(double WorldSize[2], double WorldOffset[2], double& GridVal, double MetersPerPixel, double SimulationScale);
	void DrawStateCube(bool Creation, bool OrbitPlace, double WorldSize[2]);
};