/*
 * simulateddevices.h
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#ifndef SIMULATEDDEVICES_H_
#define SIMULATEDDEVICES_H_

#include <actuator.h>


/**
 * SimulatedDriveSystem
 *
 * Will simply move the robot associated herewith in the world.
 * This happens instantaneously.
 */
class SimulatedDriveSystem : public ISimpleDriveSystem {
public:
	SimulatedDriveSystem(SimulatedRobot *robot, SimulatedWorld *world)
	: robot(robot), world(world){}
	virtual ~SimulatedDriveSystem();

	/**
	 * Moves the robot forward for a number of squares.
	 */
	virtual void moveFoward(int squares);

	/**
	 * Turns the robot either left, right, or not at all.
	 */
	virtual void turn(TurnDirection dir);

private:
	SimulatedRobot *robot;
	SimulatedWorld *world;
};

/**
 * SimulatedClaw
 *
 * Carries out the simulated 'pick up' action.
 */
class SimulatedClaw : public ISimpleClaw {
public:
	SimulatedClaw(SimulatedRobot *robot, SimulatedWorld *world)
	: robot(robot), world(world){}
	virtual ~SimulatedClaw();

	virtual void pickup();
private:
	SimulatedRobot *robot;
	SimulatedWorld *world;
};

#endif /* SIMULATEDDEVICES_H_ */
