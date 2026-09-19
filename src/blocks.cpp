#include "blocks.h"
#include <vector>

void BlocksManager::CreateNewPhysicsObject(std::vector<CombinedBlock>& Blocks, SDL_FRect& mouse) {
	Blocks.push_back({ { {1e16}, {0, 0}, {0, 0} }, { {mouse.x, mouse.y, 20, 20} } });
}