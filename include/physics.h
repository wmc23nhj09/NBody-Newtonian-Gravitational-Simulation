#pragma once
#include "blocks.h"
#include <vector>
#include <array>

class Physics {
public:
	void ApplyGravity(std::vector<CombinedBlock>& Blocks, double GravitationalConstant, double dt, double SimulationScale, double MetersPerPixel);
	std::vector<std::array<double, 2>> GetNewBlockInstancePath(std::vector<CombinedBlock>& Blocks, double GravitationalConstant, double SimulationScale, double InitialVel[2], double mass, double& CreationX, double& CreationY, SDL_FRect mouse, double WorldCenter[2], double WorldOffset[2], double MetersPerPixel, CombinedBlock& NewInstance, double dt);
	void Collision(std::vector<CombinedBlock>& Blocks);
	CombinedBlock OrbitPlaceCalculation(int* SelectedBlock, std::vector<CombinedBlock>& Blocks, SDL_FRect mouse, double GravitationalConstant, double SimulationScale, double MetersPerPixel, double mass, double dt, double WorldOffset[2], double WorldCenter[2]);
};