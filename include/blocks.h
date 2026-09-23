#pragma once

#include <SDL3/SDL.h>
#include <vector>

struct PhysicsState {
	double mass{ 1e16 };
	double velocity[2]{ 0,0 };
	double new_accel[2]{0, 0};
};

struct RenderingState {
	SDL_FRect rect;
};

struct CombinedBlock {
	PhysicsState physics;
	RenderingState rendering;
};

class BlocksManager {
public:
	void CreateNewPhysicsObject(std::vector<CombinedBlock>& Blocks, SDL_FRect& mouse, double SimulationScale, double WorldCenter[2], double WorldOffset[2], double InitialVel[2], double mass, double rho);
};