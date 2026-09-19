#include "renderer.h"
#include "blocks.h"
#include <vector>
#include <SDL3/SDL.h>

Renderer::Renderer(SDL_Renderer* renderer) {
	this->renderer = renderer;
};

void Renderer::Draw(SDL_Renderer* renderer, std::vector<CombinedBlock>& Blocks, double SimulationScale, double WorldSize[2]) {
	double WorldCenter[2] = { WorldSize[0] / 2, WorldSize[1] / 2 };

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

	for (int i = 0; i < Blocks.size(); i++) {

		if (Blocks[i].rendering.rect.w / SimulationScale > 1 && Blocks[i].rendering.rect.h / SimulationScale > 1) {


			float RenderingCenter[2] = { Blocks[i].rendering.rect.x + Blocks[i].rendering.rect.w, Blocks[i].rendering.rect.y + Blocks[i].rendering.rect.h };

			float RenderingWidth = Blocks[i].rendering.rect.w / SimulationScale;
			float RenderingHeight = Blocks[i].rendering.rect.h / SimulationScale;

			//float RenderingX = Blocks[i].rendering.rect.x + RenderingWidth / SimulationScale;
			//float RenderingY = Blocks[i].rendering.rect.y + RenderingHeight / SimulationScale;

			//float RenderingX = RenderingCenter[0] - RenderingWidth / 2; 
			//float RenderingY = RenderingCenter[1] - RenderingHeight / 2;

			float RenderingX = WorldCenter[0] + (Blocks[i].rendering.rect.x - WorldCenter[0]) / SimulationScale;
			float RenderingY = WorldCenter[1] + (Blocks[i].rendering.rect.y - WorldCenter[1]) / SimulationScale;

			SDL_FRect Rect = {RenderingX, RenderingY, RenderingWidth, RenderingHeight};

			SDL_RenderFillRect(renderer, &Rect);
		}
		else {
			continue;
		}

	}

}