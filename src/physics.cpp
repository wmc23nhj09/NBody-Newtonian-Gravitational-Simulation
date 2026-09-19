#include "physics.h"
#include "blocks.h"
#include <vector>
#include <iostream>

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

            double r = pixel_distance * MetersPerPixel;

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