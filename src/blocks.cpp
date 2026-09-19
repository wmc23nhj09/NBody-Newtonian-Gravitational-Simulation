#include "blocks.h"
#include <vector>

void BlocksManager::CreateNewPhysicsObject(std::vector<CombinedBlock>& Blocks, SDL_FRect& mouse, double SimulationScale, double WorldCenter[2]) {
	//float CreationX = WorldCenter[0] + (mouse.x - WorldCenter[0]) / SimulationScale;
	//float CreationY = WorldCenter[1] + (mouse.y - WorldCenter[1]) / SimulationScale;

	float CreationX = (mouse.x - WorldCenter[0]) * SimulationScale + WorldCenter[0];
	float CreationY = (mouse.y - WorldCenter[1]) * SimulationScale + WorldCenter[1];

	Blocks.push_back({ { {1e16}, {0, 0}, {0, 0} }, { {CreationX, CreationY, 20, 20}}});
}