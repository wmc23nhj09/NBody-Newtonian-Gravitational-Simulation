#pragma once
#include <SDL3/SDL.h>
#include <imgui.h>
#include "window.h"
#include "renderer.h"
#include "blocks.h"
#include "physics.h"
#include "UI.h"
#include <vector>
#include <array>

class Game {
public:
	Game();

	void run();

private:
	Window window;
	Renderer renderer;
	bool running;
	SDL_Event e;
	const double GravitationalConstant;
	std::vector<CombinedBlock> Blocks;
	CombinedBlock NewInstance;
	double CreationBlockMass;
	Physics physics;
	BlocksManager blocksManager;
	UI ui;
	ImGuiWindowFlags window_flags;
	double dt;
	double SimulationScale;
	double rho;
	SDL_FRect mouse;
	double WorldSize[2];
	double tempMousepos[2];
	double WorldOffset[2];
	double PrevWorldOffset[2];
	bool Dragging;
	bool CreationDragging;
	bool ShowInteractionLines;
	bool BlockPropertyCreationMenu;
	bool Creation;
	std::vector<std::array<double, 2>> Path;
	double CreationX;
	double CreationY;
	double InitialVel[2];
};