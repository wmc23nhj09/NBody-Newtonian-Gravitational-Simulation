#include "game.h"
#include "window.h"
#include "renderer.h"
#include "blocks.h"
#include <iostream>

Game::Game() :
	window(),
	renderer(window.renderer),
	running(true),
	e(),
	GravitationalConstant(6.67433e-11),
	Blocks{
		{ {1e24, {0, 0}, {0, 0}}, {{100, 100, 20, 20}}}
	},
	physics(),
	blocksManager(),
	dt(),
	MetersPerPixel(1e2),
	SimulationScale(1),
	mouse{1, 1, 1, 1}
{
}

void Game::run() {
	Uint64 framesbefore = SDL_GetPerformanceCounter();
	while (running) {
		Uint64 framesnow = SDL_GetPerformanceCounter();

		dt = ((double)(framesnow - framesbefore) / SDL_GetPerformanceFrequency());

		SDL_GetMouseState(&mouse.x, &mouse.y);

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
				running = false;
			}

			if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				blocksManager.CreateNewPhysicsObject(Blocks, mouse);
			}

		}

		renderer.Draw(window.renderer, Blocks);
		physics.ApplyGravity(Blocks, GravitationalConstant, dt, MetersPerPixel, SimulationScale);

		physics.Collision(Blocks);
		SDL_RenderPresent(window.renderer);

		framesbefore = framesnow;
	}
};