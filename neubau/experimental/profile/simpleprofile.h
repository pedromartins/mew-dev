#ifndef SIMPLE_PROFILE_H
#define SIMPLE_PROFILE_H

#include <device/virtualdevices.h>
#include <experimental/virtual/virtualworld.h>
#include <experimental/virtual/entity.h>
#include <boost/shared_ptr.hpp>

/**
 * This profile describes is a:
 * - sensorless robot
 * - simple drive system
 * - has a claw!! RARRR!
 * - grid-based world.
 * - has no task or means of control.
 */
class  SimpleRobot : public IEntity {
public:
	/**
	 * Puts the virtual robot into the virtual world at the given
	 * location and orientation.
	 * @param world
	 * @param initial_loc
	 * @param orientation
	 * @return
	 */
	SimpleRobot(Vector2di initial_loc, Orientation orientation)
	{
		/// TODO initialize a model.
	}

	virtual ~SimpleRobot() {
		delete drivesystem;
		delete claw;
	}

	/**
	 * Retrieve information from sensors!
	 * (This thing doesn't have any... :(
	 * @return
	 */
	// Vector2df getPosition();

	/**
	 * Retrieve information from orientation sensors!
	 * (This thing doesn't have any either)
	 * @return
	 */
	// Orientation getOrientation();

	// Is the robot holding something? Does the robot know anything
	// about itself?
	// bool isGrabbing() { return grabbing; }

	/**
	 * DIRECT DRIVE CONTROL METHOD
	 * Instructs this robot to move forward one square in the
	 * current orientation, and stop. This is assumed to occur
	 * instantaneously.
	 */

	virtual void moveForward(int squares) {
		cout<< "before";
		drivesystem->moveForward(squares);
		cout<< "after";
	}

	/**
	 * DIRECT DRIVE CONTROL METHOD
	 * Instructs this robot to turn
	 * Turn 90º left or right.
	 * this is assumed to occur instantaneously.
	 */
	virtual void turn(TurnDirection dir) {
		drivesystem->turn(dir);
	}

	/**
	 * DIRECT BUILD CONTROL METHOD
	 */
	void pickUp() {
		claw->close();
	}

	void dropDown() {
		claw->open();
	}

	virtual std::string toString() const {
		return "Robot ";
	}
protected:
	ISimpleDriveSystem *drivesystem;
	ISimpleClaw *claw;
};

/**
 * A Virtualized SimpleRobot.
 * - sensorless robot
 * - simple drive system
 * - has a claw!! RARRR!
 * - grid-based world.
 * - has no task or means of control.
 */
class SimpleVirtualRobot : public SimpleRobot {
public:
	SimpleVirtualRobot(VirtualWorld *world,
			Vector2di initial_loc,
			Orientation orientation)
	: SimpleRobot(initial_loc,orientation){
		drivesystem = new SimpleVirtualDrive(EntityPtr(this), world);
		claw = new SimpleVirtualClaw(EntityPtr(this), world);
	}

	virtual ~SimpleVirtualRobot() {}
};


#endif //SIMPLE_PROFILE_H
