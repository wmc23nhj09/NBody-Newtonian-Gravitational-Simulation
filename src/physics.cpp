#include "physics.h"
#include "blocks.h"
#include <vector>
#include <iostream>
#include <array>

void Physics::ApplyGravity(std::vector<CombinedBlock>& Blocks,double GravitationalConstant,double dt, double MetersPerPixel){

    for (auto& block : Blocks) {
        block.physics.new_accel[0] = 0.0;
        block.physics.new_accel[1] = 0.0;
    }

    for (size_t i = 0; i < Blocks.size(); i++) {
        for (size_t j = i + 1; j < Blocks.size(); j++) {

            double dx = Blocks[j].rendering.rect.x - Blocks[i].rendering.rect.x;

            double dy = Blocks[j].rendering.rect.y - Blocks[i].rendering.rect.y;

            double pixel_distance = std::sqrt(dx * dx + dy * dy);

            if (pixel_distance < 0.000001) {
                continue;
            }

            double r = pixel_distance;

            double force = GravitationalConstant * (Blocks[i].physics.mass * Blocks[j].physics.mass) / (r * r);


            double accel_i = force / Blocks[i].physics.mass;

            Blocks[i].physics.new_accel[0] += accel_i * (dx / pixel_distance);
            Blocks[i].physics.new_accel[1] += accel_i * (dy / pixel_distance);

            double accel_j = force / Blocks[j].physics.mass;

            Blocks[j].physics.new_accel[0] -= accel_j * (dx / pixel_distance);
            Blocks[j].physics.new_accel[1] -= accel_j * (dy / pixel_distance);

             /*std::cout <<
                "Object I: \n"
                << "    Acceleration (x, y) : " << Blocks[i].physics.new_accel[0] << ", " << Blocks[i].physics.new_accel[1] << '\n'
                << "    Velocity (x, y): " << Blocks[i].physics.velocity[0] << ", " << Blocks[i].physics.velocity[1] << '\n'
                << "    Mass: " << Blocks[i].physics.mass << '\n'

                <<

                "Object J: \n"
                << "    Acceleration (x, y) : " << Blocks[j].physics.new_accel[0] << ", " << Blocks[j].physics.new_accel[1] << '\n'
                << "    Velocity (x, y): " << Blocks[j].physics.velocity[0] << ", " << Blocks[j].physics.velocity[1] << '\n'
                << "    Mass: " << Blocks[j].physics.mass << '\n'

                << "\n Distance: " << pixel_distance << " px \n'"
                << "\n Distance: " << r << " meters" << '\n';*/
        }
    }

    for (auto& block : Blocks) {
        block.physics.velocity[0] += block.physics.new_accel[0] * dt;

        block.physics.velocity[1] += block.physics.new_accel[1] * dt;

        block.rendering.rect.x += block.physics.velocity[0] * dt / MetersPerPixel;

        block.rendering.rect.y += block.physics.velocity[1] * dt / MetersPerPixel;
    }
}

std::vector<std::array<double, 2>> Physics::GetNewBlockInstancePath(std::vector<CombinedBlock>& Blocks, double GravitationalConstant, double MetersPerPixel, double InitialVel[2], double mass, double& CreationX, double& CreationY, SDL_FRect mouse, double WorldCenter[2], double WorldOffset[2], double SimulationScale, CombinedBlock& NewInstance, double dt) {
    std::vector<std::array<double, 2>> Path;

    double LastPathX = 0;
    double LastPathY = 0;
    
    CreationX = (mouse.x - WorldCenter[0]) * SimulationScale + WorldCenter[0];
    CreationY = (mouse.y - WorldCenter[1]) * SimulationScale + WorldCenter[1];
    
    double steps = 2000.0f;
    Path.reserve(steps);

    double PredictedX = CreationX - (float)WorldOffset[0];
    double PredictedY = CreationY - (float)WorldOffset[1];

    double SimDt = dt;

    double Mass = pow(10, mass);

    NewInstance = { { {Mass}, {InitialVel[0], InitialVel[1]}, {0, 0} }, {{(float)CreationX - (float)WorldOffset[0], (float)CreationY - (float)WorldOffset[1], 20, 20}} };

    double PredictedVel[2] = { InitialVel[0], InitialVel[1] };

    double PredictedAcceleration[2] = {NewInstance.physics.new_accel[0] ,  NewInstance.physics.new_accel[1]};
    
    for (int StepsTaken = 0; StepsTaken < steps; StepsTaken++) {
        if (steps == 0) {
            Path.push_back({
                    NewInstance.rendering.rect.x,
                    NewInstance.rendering.rect.y
                });
        }


        PredictedAcceleration[0] = 0.0;
        PredictedAcceleration[1] = 0.0;

        for (int i = 0; i < Blocks.size(); i++) {

            double dx = PredictedX - Blocks[i].rendering.rect.x;

            double dy = PredictedY - Blocks[i].rendering.rect.y;

            double pixel_distance = std::sqrt(dx * dx + dy * dy);

            if (pixel_distance < 0.000001) {
                continue;
            }

            double r = pixel_distance;

            double force = GravitationalConstant * (Blocks[i].physics.mass * NewInstance.physics.mass) / (r * r);

            double accel_j = force / NewInstance.physics.mass;

            PredictedAcceleration[0] -= accel_j * (dx / pixel_distance);
            PredictedAcceleration[1] -= accel_j * (dy / pixel_distance);

        }

        PredictedVel[0] += PredictedAcceleration[0] * dt;
        PredictedVel[1] += PredictedAcceleration[1] * dt;

        PredictedX += PredictedVel[0] * dt / MetersPerPixel;
        PredictedY += PredictedVel[1] * dt / MetersPerPixel;

        Path.push_back({
                PredictedX,
                PredictedY
            });
    }
    return Path;
}

void Physics::Collision(std::vector<CombinedBlock>& Blocks) {
	for (size_t i = 0; i < Blocks.size(); i++) {
		bool erased = false;
		for (size_t j = i+1; j < Blocks.size(); j++) {

			if (Blocks[i].rendering.rect.x <= Blocks[j].rendering.rect.x + Blocks[j].rendering.rect.w && Blocks[i].rendering.rect.x + Blocks[i].rendering.rect.w >= Blocks[j].rendering.rect.x && Blocks[i].rendering.rect.y <= Blocks[j].rendering.rect.y + Blocks[j].rendering.rect.h && Blocks[i].rendering.rect.y + Blocks[i].rendering.rect.h >= Blocks[j].rendering.rect.y) {
				Blocks.erase(Blocks.begin() + j);
				Blocks.erase(Blocks.begin() + i);

				erased = true;
				break;
			}
		}

		if (erased) {
			i--;
		}
	}
}