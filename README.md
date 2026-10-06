# NBody-Newtonian-Gravitational-Simulation
* A program written in C++ with SDL3 to simulate how bodies interact in deep space via gravity

# Overview
* This program was coded in C++, with SDL3 used as the visual help.

# Features
* Gravity
* Block Spawning
* Collision Handeling~
* Screen Scaling
* Block Property Changing~
* Scalable size
* Pre-spawning trajectory path
* Automatic orbit creator
* Time Control (very loose) 
* Interchangeable pixel to meter ratio
* Trail lines of 1 chosen object or all objects in the simulation
* Circles around each object to see them at a distance

## Trail Lines
![Trail lines in use](media/'Show trajectory line.gif')

# Future Features
* Energy Conservation
* Angular Momentum
* Barnes hut algorithm
* etc.

# Known Limitations
* Cannot delete objects individiually
* Same block size regardless of mass
* Current scale has users creating scenearios at real world scale, cause weird behavior (Scaling and time scale issues) 
* Time scale only goes from 0x and 1x
