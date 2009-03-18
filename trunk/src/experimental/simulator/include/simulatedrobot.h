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
	// Get orientation from sensors.
	Orientation getOrientation();

	// Is the robot holding something?
	bool isGrabbing() { return grabbing; }

	/**
	 * DIRECT DRIVE CONTROL METHOD
	 * Instructs this robot to move forward one square in the
	 * current orientation, and stop. This is assumed to occur
	 * instantaneously.
	 */
	void moveForward();

	/**
	 * DIRECT BUILD CONTROL METHOD
	 */
	void pickUp();

	/**
	 * DIRECT DRIVE CONTROL METHOD
	 * Instructs this robot to turn
	 * Turn 90º left or right.
	 * this is assumed to occur instantaneously.
	 */
	void turn(TurnDirection dir);

private:
	bool grabbing = false;
	Perceptor *perceptor;
	ISimpleDriveSystem *drivesystem;
	ISimpleClaw *claw;
};

#endif //SIMULATED_ROBOT_H
