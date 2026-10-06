#pragma once

#include <SDL3/SDL.h>
#include <vector>

struct PhysicsState {
	double mass{ 1 };
	double velocity[2]{ 0,0 };
	double new_accel[2]{0, 0};
};

struct TrailPoint {
	float x;
	float y;
	float time;
};

struct RenderingState {
	SDL_FRect rect;
	int id;
	std::vector<TrailPoint> trails;
};

struct InteractionState {
	bool clicked{ false };
	bool hoveringOver{ false };
};

struct CombinedBlock {
	PhysicsState physics;
	RenderingState rendering;
	InteractionState interaction;
};

class BlocksManager {
public:
	void CreateNewPhysicsObject(std::vector<CombinedBlock>& Blocks, SDL_FRect& mouse, double SimulationScale, double WorldCenter[2], double WorldOffset[2], double InitialVel[2], double mass, double rho);
	void GetHeldState(std::vector<CombinedBlock>& Blocks, SDL_FRect mouse, double WorldOffset[2], double WorldCenter[2], double SimulationScale, bool ClickCheck);
	void SetTrails(std::vector<CombinedBlock>& Blocks, double SimTime, int* SelectedBlock);
};