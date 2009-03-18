
#include "include/simulatedrobot.h"
#include <time.h>



SimulatedRobot::SimulatedRobot(
		SimulatedWorld *world,
		GridModel *model,
		Vector2di initial_loc,
		Orientation orientation)
: model(model), position(position), orientation(orientation) {

//	locator = new SimulatedLocator(this,world);
//	orientator = new SimulatedOrientator(this,world);

	drivesystem = new SimulatedDriveSystem(this,world);

}

SimulatedRobot::~BasicRobot(){
	delete perceptor;
	delete drivesystem;
}

/**
 * Returns the best estimate of the current position
 */
Vector2di SimulatedRobot::getLocation() {

}


// Move the robot forward
void SimulatedRobot::moveForward() {
	drivesystem->moveFoward(1);
}


void SimulatedRobot::pickUp() {
	claw->pickup();
}


void SimulatedRobot::turn(TurnDirection dir) {
	drivesystem->turn(dir);
}
