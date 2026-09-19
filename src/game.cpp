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
		{ {1e16, {0, 0}, {0, 0}}, {{100, 100, 20, 20}}}
	},
	physics(),
	blocksManager(),
	dt(),
	SimulationScale(1),
	mouse{1, 1, 1, 1},
	WorldSize{}
{
}

void Game::run() {
	Uint64 framesbefore = SDL_GetPerformanceCounter();
	while (running) {
		SDL_GetWindowSizeInPixels(window.window, &window.WindowWidth, &window.WindowHeight);

		WorldSize[0] = (double)window.WindowWidth;
		WorldSize[1] = (double)window.WindowHeight;

		double WorldCenter[2] = { WorldSize[0] / 2, WorldSize[1] / 2 };


		Uint64 framesnow = SDL_GetPerformanceCounter();

		dt = ((double)(framesnow - framesbefore) / SDL_GetPerformanceFrequency());

		SDL_GetMouseState(&mouse.x, &mouse.y);

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
				running = false;
			}

			if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				blocksManager.CreateNewPhysicsObject(Blocks, mouse, SimulationScale, WorldCenter);
			}

			if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_MINUS) {
				if (SimulationScale + 1 <= 1e6) {
					SimulationScale += 1;
				}
			}

			else if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_EQUALS) {
				if (SimulationScale - 1 >= 1) {
					SimulationScale -= 1;
				}
			}

		}

		renderer.Draw(window.renderer, Blocks, SimulationScale, WorldSize);
		physics.ApplyGravity(Blocks, GravitationalConstant, dt, SimulationScale);

		physics.Collision(Blocks);
		SDL_RenderPresent(window.renderer);

		framesbefore = framesnow;
	}
};