#include "renderer.h"
#include "blocks.h"
#include <vector>
#include <SDL3/SDL.h>

Renderer::Renderer(SDL_Renderer* renderer) {
	this->renderer = renderer;
};

void Renderer::Draw(SDL_Renderer* renderer, std::vector<CombinedBlock>& Blocks) {

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

	for (int i = 0; i < Blocks.size(); i++) {
		SDL_RenderFillRect(renderer, &Blocks[i].rendering.rect);
	}

}