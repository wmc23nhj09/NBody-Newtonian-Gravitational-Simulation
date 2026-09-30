#include "blocks.h"
#include <vector>
#include <numbers>
#include <iostream>

void BlocksManager::CreateNewPhysicsObject(std::vector<CombinedBlock>& Blocks, SDL_FRect& mouse, double SimulationScale, double WorldCenter[2], double WorldOffset[2], double InitialVel[2], double mass, double rho) {
	//PROVEN

	float CreationX = (mouse.x - WorldCenter[0]) * SimulationScale + WorldCenter[0];
	float CreationY = (mouse.y - WorldCenter[1]) * SimulationScale + WorldCenter[1];

	double Mass = pow(10, mass);

	double physicalRadius = sqrt(mass / (std::numbers::pi * rho));

	float visualRadius = 20;

	Blocks.push_back({ { {Mass}, {InitialVel[0], InitialVel[1]}, {0, 0} }, {{CreationX - (float)WorldOffset[0], CreationY - (float)WorldOffset[1], visualRadius, visualRadius}}, {false} });
}

void BlocksManager::GetHeldState(std::vector<CombinedBlock>& Blocks, SDL_FRect mouse, double WorldOffset[2], double WorldCenter[2], double SimulationScale) {
	//PROVEN

	double ChangedX = (mouse.x - WorldCenter[0]) * SimulationScale + WorldCenter[0] - WorldOffset[0];
	double ChangedY = (mouse.y - WorldCenter[1]) * SimulationScale + WorldCenter[1] - WorldOffset[1];


	for (auto& b : Blocks) {

		double BlockChangedX = (b.rendering.rect.x - WorldCenter[0]) + WorldCenter[0];
		double BlockChangedY = (b.rendering.rect.y - WorldCenter[1]) + WorldCenter[1];

		b.interaction.clicked = false;

		if (ChangedX < BlockChangedX + b.rendering.rect.w && ChangedX + mouse.w > BlockChangedX && ChangedY < BlockChangedY + b.rendering.rect.h && ChangedY + mouse.h > BlockChangedY) {

			b.interaction.clicked = true;
			break;

		}
	}
}