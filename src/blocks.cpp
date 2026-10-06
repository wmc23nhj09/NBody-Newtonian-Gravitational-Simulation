#include "blocks.h"
#include <vector>
#include <numbers>
#include <iostream>

void BlocksManager::CreateNewPhysicsObject(std::vector<CombinedBlock>& Blocks, SDL_FRect& mouse, double SimulationScale, double WorldCenter[2], double WorldOffset[2], double InitialVel[2], double mass, double rho) {
	//PROVEN
	int ID = Blocks.size();

	float CreationX = (mouse.x - WorldCenter[0]) * SimulationScale + WorldCenter[0];
	float CreationY = (mouse.y - WorldCenter[1]) * SimulationScale + WorldCenter[1];

	double physicalRadius = sqrt(mass / (std::numbers::pi * rho));

	float visualRadius = 20;

	Blocks.push_back({ { {mass},{InitialVel[0], InitialVel[1]}, {0, 0}}, {{CreationX - (float)WorldOffset[0], CreationY - (float)WorldOffset[1], visualRadius, visualRadius}, { ID }, {} }, { {false}, {false}} });
}

void BlocksManager::GetHeldState(std::vector<CombinedBlock>& Blocks, SDL_FRect mouse, double WorldOffset[2], double WorldCenter[2], double SimulationScale, bool ClickCheck) {
	//PROVEN

	double ChangedX = (mouse.x - WorldCenter[0]) * SimulationScale + WorldCenter[0] - WorldOffset[0];
	double ChangedY = (mouse.y - WorldCenter[1]) * SimulationScale + WorldCenter[1] - WorldOffset[1];
 

	for (auto& b : Blocks) {

		double BlockChangedX = (b.rendering.rect.x - WorldCenter[0]) + WorldCenter[0];
		double BlockChangedY = (b.rendering.rect.y - WorldCenter[1]) + WorldCenter[1];

		double Blockw = b.rendering.rect.h * SimulationScale;
		double Blockh = b.rendering.rect.h * SimulationScale;

		b.interaction.clicked = false;
		b.interaction.hoveringOver = false;

		if (ChangedX < BlockChangedX + Blockw && ChangedX + mouse.w > BlockChangedX && ChangedY < BlockChangedY + Blockh && ChangedY + mouse.h > BlockChangedY) {

			if (ClickCheck) {
				b.interaction.clicked = true;
			}
			else {
				b.interaction.hoveringOver = true;
			}
			break;
		}
	}
}

void BlocksManager::SetTrails(std::vector<CombinedBlock>& Blocks, double SimTime, int* SelectedBlock) {
	for (auto& b : Blocks) {
		if (b.rendering.id == *SelectedBlock) {
			TrailPoint trailsToAdd = {b.rendering.rect.x, b.rendering.rect.y, SimTime};
			b.rendering.trails.push_back(trailsToAdd);
		}
	}
}