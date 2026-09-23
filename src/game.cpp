#include "game.h"
#include "window.h"
#include "renderer.h"
#include "blocks.h"
#include "UI.h"
#include <iostream>
#include <imgui_impl_sdlrenderer3.h>
#include <imgui_impl_sdl3.h>
#include <numbers>

Game::Game() :
	window(),
	renderer(window.renderer),
	running(true),
	e(),
	GravitationalConstant(6.67433e-11),
	Blocks{
	},
	NewInstance{},
	CreationBlockMass{ 15 },
	physics(),
	blocksManager(),
	ui(),
	window_flags(),
	dt(),
	SimulationScale(1),
	rho(1),
	mouse{ 1, 1, 1, 1 },
	WorldSize{},
	tempMousepos{ -1, -1 },
	WorldOffset{ 1, 1 },
	PrevWorldOffset{ 0, 0 },
	Dragging(false),
	CreationDragging(false),
	ShowInteractionLines(false),
	BlockPropertyCreationMenu(false),
	Creation(false),
	Path{},
	CreationX(),
	CreationY(),
	InitialVel{0, 0}
{
}

void Game::run() {
	ImGui::CreateContext();
	ImGui_ImplSDL3_InitForSDLRenderer(window.window, renderer.renderer);
	ImGui_ImplSDLRenderer3_Init(renderer.renderer);
	Uint64 framesbefore = SDL_GetPerformanceCounter();

	while (running) {
		SDL_GetWindowSizeInPixels(window.window, &window.WindowWidth, &window.WindowHeight);


		Uint64 framesnow = SDL_GetPerformanceCounter();

		dt = ((double)(framesnow - framesbefore) / SDL_GetPerformanceFrequency());

		SDL_GetMouseState(&mouse.x, &mouse.y);

		WorldSize[0] = (double)window.WindowWidth;
		WorldSize[1] = (double)window.WindowHeight;


		double WorldCenter[2] = { window.WindowWidth/2, window.WindowHeight/2};

		ui.SetFlags(window_flags);

		while (SDL_PollEvent(&e)) {
			ImGui_ImplSDL3_ProcessEvent(&e);

			if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) {
				running = false;
			}

			if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_Q) {
				Creation = !Creation;
			}

			if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {

				if (e.button.button == SDL_BUTTON_LEFT && Creation) {
					if (tempMousepos[0] == -1) {
						tempMousepos[0] = mouse.x;
						tempMousepos[1] = mouse.y;
					}
					CreationDragging = true;

				}

				else if (e.button.button == SDL_BUTTON_RIGHT) {
					Dragging = true;
				}

			}

			else if (e.type == SDL_EVENT_MOUSE_WHEEL) {
				float y = e.wheel.y;

				if (y < 0) {

					if (SimulationScale + 1 <= 1e6) {
						SimulationScale += 1;
					}

				}
				else if (y > 0) {

					if (SimulationScale - 1 >= 1) {
						SimulationScale -= 1;
					}

				}
			}

			if (e.type == SDL_EVENT_MOUSE_BUTTON_UP) {
				if (e.button.button == SDL_BUTTON_RIGHT) {
					tempMousepos[0] = -1;
					Dragging = false;

					PrevWorldOffset[0] = WorldOffset[0];
					PrevWorldOffset[1] = WorldOffset[1];
				}
				else if (e.button.button == SDL_BUTTON_LEFT && Creation){
					SDL_FRect TempRect{ tempMousepos[0], tempMousepos[1], mouse.w, mouse.h };

					std::cout << InitialVel[0] << ", " << InitialVel[1] << '\n';

					blocksManager.CreateNewPhysicsObject(Blocks, TempRect, SimulationScale, WorldCenter, WorldOffset, InitialVel, CreationBlockMass, rho);


					tempMousepos[0] = -1;
					CreationDragging = false;

					Path.clear();
				}
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

			if (e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_R) {
				Blocks.clear();
			}

		}

		if (Dragging) {
			if (tempMousepos[0] == -1) {

				tempMousepos[0] = mouse.x;
				tempMousepos[1] = mouse.y;

			}
			WorldOffset[0] = PrevWorldOffset[0] - ((tempMousepos[0] - mouse.x)*SimulationScale);
			WorldOffset[1] = PrevWorldOffset[1] - ((tempMousepos[1] - mouse.y)*SimulationScale);
		}

		if (CreationDragging) {
			double angle = atan2(tempMousepos[1] - mouse.y, tempMousepos[0] - mouse.x) + std::numbers::pi;
			double magnitude = sqrt(pow((mouse.x - tempMousepos[0]), 2) + pow((mouse.y - tempMousepos[1]), 2));

			magnitude *= SimulationScale * SimulationScale;

			InitialVel[0] = cos(angle) * magnitude;
			InitialVel[1] = sin(angle) * magnitude;

			SDL_FRect rect = {tempMousepos[0], tempMousepos[1], 20, 20};

			Path = physics.GetNewBlockInstancePath(Blocks, GravitationalConstant, SimulationScale, InitialVel, CreationBlockMass, CreationX, CreationY, rect, WorldCenter, WorldOffset, SimulationScale, NewInstance, dt);
		}

		renderer.Draw(window.renderer, Blocks, SimulationScale, WorldCenter, WorldOffset, ShowInteractionLines, Path);
		physics.ApplyGravity(Blocks, GravitationalConstant, dt, SimulationScale);

		physics.Collision(Blocks);

		ui.DrawUI(window.renderer, window_flags, BlockPropertyCreationMenu, window.WindowWidth, window.WindowHeight, CreationBlockMass, (float&)rho);
		SDL_RenderPresent(window.renderer);

		framesbefore = framesnow;
	}
};