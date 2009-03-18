/*
 * simulation.cpp
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#include "include/simulation.h"
#include <perception.h>


Simulation::Simulation() {
	world = new SimulatedWorld(1);
	model = new GridModel(world->getWidth(), world->getHeight());
	robot = new SimulatedRobot(world, model, Vector2di(0,0), NORTH);
}

Simulation::~Simulation() {
	delete robot;
	delete world;
}


void Simulation::run(){
	robot->moveForward();
	world->show();
}
