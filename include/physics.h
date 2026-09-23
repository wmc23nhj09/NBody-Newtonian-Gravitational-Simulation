#pragma once
#include "blocks.h"
#include <vector>
#include <array>

class Physics {
public:
	void ApplyGravity(std::vector<CombinedBlock>& Blocks, double GravitationalConstant, double dt, double MetersPerPixel);
	std::vector<std::array<double, 2>> GetNewBlockInstancePath(std::vector<CombinedBlock>& Blocks, double GravitationalConstant, double MetersPerPixel, double InitialVel[2], double mass, double& CreationX, double& CreationY, SDL_FRect mouse, double WorldCenter[2], double WorldOffset[2], double SimulationScale, CombinedBlock& NewInstance, double dt);
	void Collision(std::vector<CombinedBlock>& Blocks);
};