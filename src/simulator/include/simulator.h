#ifndef SIM_H
#define SIM_H

/*
  mew Robot Simulator - 2009
  v.0.1 : Initial meeting 21/01/09
 */

#define PROB_FAILURE_PICKUP 0.1
#define PROB_DROP_MOVING 0.1

// **** MAP KNOWLEDGE ****
#define SIZE_X 10
#define SIZE_Y 10


#include <vector2d.h>

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
	SimulatedRobot(IGridModel *model, Vector2di initial_loc, Orientation orientation);

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
	void loadMap(int i);

private:

	// State:
	Orientation orientation;
	int mapNum = 0;
	bool grabbing = false;
	bool inited = false;

};

#endif //SIM_H
