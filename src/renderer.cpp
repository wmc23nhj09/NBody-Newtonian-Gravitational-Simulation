#include "renderer.h"
#include "blocks.h"
#include <vector>
#include <SDL3/SDL.h>
#include <iostream>

Renderer::Renderer(SDL_Renderer* renderer) {
	this->renderer = renderer;
};

void Renderer::Draw(SDL_Renderer* renderer, std::vector<CombinedBlock>& Blocks, double SimulationScale, double WorldCenter[2], double WorldOffset[2], bool ShowInteractionLines, bool ShowAllOrbitLines,std::vector<std::array<double, 2>> Path, bool CreationTable, bool Creation, bool OrbitPlace, int* SelectedBlock, double SimTime) {

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

	for (int i = 0; i < Blocks.size(); i++) {

		if (SelectedBlock != nullptr || ShowAllOrbitLines) {

			double MaxTrailTimer = 2;

			for (int TrailKeep = 1; TrailKeep < Blocks[i].rendering.trails.size(); TrailKeep++) {

				const auto& BlockTrails = Blocks[i].rendering.trails;

				if (abs(BlockTrails[TrailKeep].time - SimTime) < MaxTrailTimer) {

					float x1 = (WorldCenter[0] + ((BlockTrails[TrailKeep - 1].x - WorldCenter[0]) / SimulationScale)) + (WorldOffset[0] / SimulationScale);
					float y1 = (WorldCenter[1] + ((BlockTrails[TrailKeep - 1].y - WorldCenter[1]) / SimulationScale)) + (WorldOffset[1] / SimulationScale);

					float x2 = (WorldCenter[0] + ((BlockTrails[TrailKeep].x - WorldCenter[0]) / SimulationScale)) + (WorldOffset[0] / SimulationScale);
					float y2 = (WorldCenter[1] + ((BlockTrails[TrailKeep].y - WorldCenter[1]) / SimulationScale)) + (WorldOffset[1] / SimulationScale);

					SDL_RenderLine(renderer, x1, y1, x2, y2);
				}
			}
		}

		if (Blocks[i].rendering.rect.w / SimulationScale > 1 && Blocks[i].rendering.rect.h / SimulationScale > 1) {


			float RenderingCenter[2] = { Blocks[i].rendering.rect.x + Blocks[i].rendering.rect.w, Blocks[i].rendering.rect.y + Blocks[i].rendering.rect.h };

			float RenderingWidth = Blocks[i].rendering.rect.w / SimulationScale;
			float RenderingHeight = Blocks[i].rendering.rect.h / SimulationScale;

			float RenderingX = WorldCenter[0] + (Blocks[i].rendering.rect.x - WorldCenter[0]) / SimulationScale;
			float RenderingY = WorldCenter[1] + (Blocks[i].rendering.rect.y - WorldCenter[1]) / SimulationScale;

			if (ShowInteractionLines) {
				for (int j = i + 1; j < Blocks.size(); j++) {
					float RenderingXJ = WorldCenter[0] + ((Blocks[j].rendering.rect.x - WorldCenter[0]) / SimulationScale);
					float RenderingYJ = WorldCenter[1] + ((Blocks[j].rendering.rect.y - WorldCenter[1]) / SimulationScale);

					SDL_RenderLine(renderer, RenderingX + (WorldOffset[0] / SimulationScale), RenderingY + (WorldOffset[1] / SimulationScale), RenderingXJ + (WorldOffset[0] / SimulationScale), RenderingYJ + (WorldOffset[1] / SimulationScale));

				}
			}

			SDL_FRect Rect = {RenderingX + (WorldOffset[0]/SimulationScale), RenderingY + (WorldOffset[1]/SimulationScale), RenderingWidth, RenderingHeight};

			SDL_RenderFillRect(renderer, &Rect);

		}
		else {
			continue;
		}

	}

	for (size_t j = 1; j < Path.size(); ++j)
	{
		float x1 = (WorldCenter[0] + ((Path[j - 1][0] - WorldCenter[0]) / SimulationScale)) + (WorldOffset[0]/SimulationScale);
		float y1 = (WorldCenter[1] + ((Path[j - 1][1] - WorldCenter[1]) / SimulationScale)) + (WorldOffset[1] / SimulationScale);

		float x2 = (WorldCenter[0] + ((Path[j][0] - WorldCenter[0]) / SimulationScale)) + (WorldOffset[0] / SimulationScale);
		float y2 = (WorldCenter[1] + ((Path[j][1] - WorldCenter[1]) / SimulationScale)) + (WorldOffset[1] / SimulationScale);

		SDL_RenderLine(renderer, x1, y1, x2, y2);
	}


	double WorldSize[2] = {WorldCenter[0] * 2, WorldCenter[1] * 2};

	SDL_FRect corner_cube_iloveyou{ WorldSize[0] * 0.63, (float)0.6639 * WorldSize[1], WorldSize[0] - WorldSize[0] * 0.63, WorldSize[1] - (float)0.6639 * (float)WorldSize[1] };
	if (CreationTable) {
		
		SDL_FRect temp = { 120, (float)0.6639 * (float)WorldSize[1], WorldSize[0] * 0.63, (float)0.6639 * (float)WorldSize[1] };

		SDL_RenderFillRect(renderer, &temp);
	}


	if (Creation) {
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
	}
	else if (OrbitPlace) {
		SDL_SetRenderDrawColor(renderer, 255, 0, 255, 0);
	}
	else {
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
	}


	SDL_RenderFillRect(renderer, &corner_cube_iloveyou);

}