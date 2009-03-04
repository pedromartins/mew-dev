/*
 * simulateddevices.h
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#ifndef SIMULATEDDEVICES_H_
#define SIMULATEDDEVICES_H_

#include <actuator.h>

// Offsets to squares for each direction.
int frontDir[4][2] = {
	Vector2di(0,1), // north
	Vector2di(-1,0),// east
	Vector2di(0,-1),// south
	Vector2di(1,0) // west
};


/**
 * SimulatedDriveSystem
 *
 * Will simply move the robot associated herewith in the world.
 */
class SimulatedDriveSystem : public ISimpleDriveSystem {
public:
	SimulatedDriveSystem(SimulatedRobot *robot, SimulatedWorld *world)
	: robot(robot), world(world){}
	virtual ~SimulatedDriveSystem();

	/**
	 * Moves the robot forward for a number of squares.
	 */
	virtual void moveFoward(int squares){
		world->setLocationOf(robot,
				world->getLocationOf(robot)+
				frontDir[world->getOrientationOf(robot)]*squares
		);
	}

	/**
	 * Turns the robot either left, right, or not at all.
	 */
	virtual void turn(TurnDirection dir){
		if (dir != STRAIGHT)
			world->setOrientationOf(robot,
					(world->getOrientationOf(robot)+
					dir)%4
			);
	}

private:
	SimulatedRobot *robot;
	SimulatedWorld *world;
};



class SimulatedClaw : public ISimpleClaw {
public:
private:


};

#endif /* SIMULATEDDEVICES_H_ */
