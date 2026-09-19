#pragma once
#include "blocks.h"
#include <vector>

class Physics {
public:
	void ApplyGravity(std::vector<CombinedBlock>& Blocks, double GravitationalConstant, double dt, double MetersPerPixel);

	void Collision(std::vector<CombinedBlock>& Blocks);
};