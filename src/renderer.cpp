#include "renderer.h"
#include "blocks.h"
#include <vector>
#include <SDL3/SDL.h>
#include <iostream>

Renderer::Renderer(SDL_Renderer* renderer) {
	this->renderer = renderer;
};

void Renderer::Draw(SDL_Renderer* renderer, std::vector<CombinedBlock>& Blocks, double SimulationScale, double ZoomCenter[2], double WorldOffset[2], bool ShowInteractionLines, std::vector<std::array<double, 2>> Path) {

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

	for (int i = 0; i < Blocks.size(); i++) {

		if (Blocks[i].rendering.rect.w / SimulationScale > 1 && Blocks[i].rendering.rect.h / SimulationScale > 1) {


			float RenderingCenter[2] = { Blocks[i].rendering.rect.x + Blocks[i].rendering.rect.w, Blocks[i].rendering.rect.y + Blocks[i].rendering.rect.h };

			float RenderingWidth = Blocks[i].rendering.rect.w / SimulationScale;
			float RenderingHeight = Blocks[i].rendering.rect.h / SimulationScale;

			float RenderingX = ZoomCenter[0] + (Blocks[i].rendering.rect.x - ZoomCenter[0]) / SimulationScale;
			float RenderingY = ZoomCenter[1] + (Blocks[i].rendering.rect.y - ZoomCenter[1]) / SimulationScale;

			if (ShowInteractionLines) {
				for (int j = i + 1; j < Blocks.size(); j++) {
					float RenderingXJ = ZoomCenter[0] + ((Blocks[j].rendering.rect.x - ZoomCenter[0]) / SimulationScale);
					float RenderingYJ = ZoomCenter[1] + ((Blocks[j].rendering.rect.y - ZoomCenter[1]) / SimulationScale);

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
		float x1 = ZoomCenter[0] + (Path[j - 1][0] - ZoomCenter[0]) / SimulationScale;
		float y1 = ZoomCenter[1] + (Path[j - 1][1] - ZoomCenter[1]) / SimulationScale;

		float x2 = ZoomCenter[0] + (Path[j][0] - ZoomCenter[0]) / SimulationScale;
		float y2 = ZoomCenter[1] + (Path[j][1] - ZoomCenter[1]) / SimulationScale;

		SDL_RenderLine(renderer, x1, y1, x2, y2);
	}

}