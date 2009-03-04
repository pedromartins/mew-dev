#ifndef SIMULATED_ROBOT_H
#define SIMULATED_ROBOT_H

#include <core.h>
#include <basicrobot.h>

#include "simulatedlocator.h"
#include "simulatedorientator.h"
#include "simulateddevices.h"
#include "simulatedworld.h"

using namespace mew;
using namespace core;


/**
 * SimulatedRobot
 *
 * Simulated robot is a basic virtual robot that abides by the rules
 * of the simulator.
 *
 * It can:
 * moveForward,
 * pickup,
 * load another model onto the robot.
 *
 * Should be created with a model. The model is updated by the Robot.
 */
class SimulatedRobot : public BasicRobot {
	SimulatedRobot(SimulatedWorld *world,
			GridModel *model,
			Vector2di initial_loc,
			Orientation orientation);

	virtual ~SimulatedRobot();

	// Get position from the sensors
	Vector2df getPosition();

	// Is the robot holding something?
	bool isGrabbing() { return grabbing; }

	// Move the robot forward
	void moveForward();

	// Pick up what's in *front* of the robot.
	void pickUp();

	// Turn 45º left or right
	void turn(int left);

	/*  Load a different map
    (must be done before starting/reseting) */
	//void loadMap(int i);

	/**
	 * Returns true iff the position is on the board.
	 */
	bool inBoard(Vector2di newPos) {
		return (newPos.x >= 0 && newPos.x < SIZE_X &&
				newPos.y >= 0 && newPos.y < SIZE_Y);
	}

	/**
	 * Returns the logical square in front of this simulated robot.
	 */
	Vector2di inFront() {
		Vector2di front; //
		int * dir = frontDir[orientation];
		front.x = pos.x + dir[0];
		front.y = pos.y + dir[1];
		return front;
	}


private:
	bool grabbing = false;
	Perceptor *perceptor;
	ISimpleDriveSystem *drivesystem;
};

#endif //SIMULATED_ROBOT_H
