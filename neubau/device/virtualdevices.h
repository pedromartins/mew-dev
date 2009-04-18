/*
 * virtualdevicesdevices.h
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#ifndef VIRTUALDEVICES_H_
#define VIRTUALDEVICES_H_

#include "actuator.h"
#include <experimental/virtual/virtualworld.h>
#include <perception/entity.h> // relationship with a higher layer that shouldn't really exist.

#define PROB_FAILURE_PICKUP 0.1
#define PROB_DROP_MOVING 0.1

/**
 * Given a virtual world, virtualdevices are objects that carry out
 * interactions between the robot and the VirtualWorld.
 *
 * VirtualDrive carries an IEntity as
 * payload, such that the IEntity is moved whenever a call to the Virtual
 * Drive's control methods are called.
 *
 * A VirtualClaw is able to manipulate the world by 'picking up' and
 * 'dropping down' PIECEs in the VirtualWorld. A virtualclaw is
 * *mounted* onto something, typically a robot.
 * However, it is just as possible to mount the virtual claw onto any
 * other entity.
 */

/**
 * A SimpleVirtualDrive is a device that moves some Entity.
 * Most SimpleRobots use the SimpleVirtualDrive for its movement.
 */
class SimpleVirtualDrive : public ISimpleDriveSystem {
public:
	SimpleVirtualDrive(EntityPtr payload, SimpleVirtualWorld *world)
	: payload(payload), world(world){}
	virtual ~SimpleVirtualDrive() {}

	/**
	 * Moves the robot forward for a number of squares.
	 * @param squares the number of squares to move in the SimpleVirtualWorld.
	 */
	virtual void moveForward(int squares);

	/**
	 * Turns the robot either left, right, or not at all.
	 * @param dir the direction to turn in a SimpleVirtualWorld
	 */
	virtual void turn(TurnDirection dir);

private:
	EntityPtr payload;
	SimpleVirtualWorld *world;
};

/**
 * Carries out the simulated 'pick up' action.
 * In the simulated world, it removes an entity from the world,
 * loads it onto the claw, and moves with the robot.
 */
class SimpleVirtualClaw : public ISimpleClaw {
public:
	SimpleVirtualClaw(EntityPtr mountpoint, SimpleVirtualWorld *world)
	: closed(false), holding(false), mountpoint(mountpoint), world(world){}
	virtual ~SimpleVirtualClaw() {}

	virtual void close();
	virtual void open();

protected:
	bool isHolding() { return holding; }
	bool isClosed() { return closed; }

private:
	bool closed;  //default to open claw.
	bool holding; // default to empty claw.
	EntityPtr mountpoint;
	SimpleVirtualWorld *world;
};

#endif /* SIMULATEDDEVICES_H_ */
