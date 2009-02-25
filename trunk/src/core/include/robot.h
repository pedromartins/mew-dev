/*
 * robot.h
 *
 *  Created on: 15-Feb-2009
 *      Author: Hok Shun Poon
 */

#ifndef ROBOT_STATE_H_
#define ROBOT_STATE_H_

#include "core.h"

namespace mew {
namespace core {

#define ENTITY_TRAVERSAL_RADIAL 1
#define ENTITY_TRAVERSAL_UNIFORM 2
#define ENTITY_TRAVERSAL_UNIFORM_RADIAL 3

enum turn_direction_t {
	LEFT = -1,
	STRAIGHT,
	RIGHT
};

/**
 * BasicRobot
 *
 * A basic robot is a robot that simply navigates a
 * grid-based model.
 *
 * Such a robot must be able to support the most basic
 * functions such as:
 *
 * - getting its own position in terms of the grid-based
 *   model
 * - moving forward a number of squares
 * - turning left and right.
 * - stopping
 * - picking something up with its claw
 *
 * The location of a robot is only meaningful in the context
 * of its current Model.
 * If the robot has no model, i.e. model == NULL
 * then the robot must rely on odometry at all times.
 *
 */
class BasicRobot {
	/**
	 * Initializes the robot at a particular location
	 * in the given 2D grid-based model.
	 */
	BasicRobot(IGridModel *model, Vector2di initial_loc, Orientation orientation){}
	virtual ~BasicRobot();

	// Move the robot forward one grid square.
	virtual void moveForward() = 0;

	// Pick up what's in *front* of the robot.
	virtual void pickUp() = 0;

	/**
	 * Turns the robot 45º left if left is TRUE,
	 * otherwise turns the robot 45º right.
	 * @param left iff TRUE, will turn robot left, else will turn robot right.
	 */
	virtual void turn(turn_direction_t direction) = 0;

	// Get position from the sensors
	virtual Vector2di getPosition() = 0;

	/* Sets the current model to be something else entirely. */
	IGridModel *getModel() { return model; }
	void setModel(IGridModel *model) { this->model = model; }
private:
	IGridModel *model; // the current world model used.
};


/**
 * Robot
 *
 * Represents a kinematic, more complex robot.
 * A robot is typically given some sort of map that corresponds to the world
 * that it's in, and the robot updates its own StaticState with respect to the the world
 * loaded as well as sensor readings.
 *
 * If no map is loaded into the robot, then a default blank map is used.
 */
class Robot : public KinematicEntity {
public:
	virtual ~Robot() {}

	/** Updates the state of the robot by polling everything and updating the robot's model. */
	virtual void updateState() = 0;

	/* Getters - actually polls devices and  */
	virtual Vector2df getPosition();
	virtual float getOrientation();
	virtual Vector2df getVelocity();
	virtual float getAngularVelocity();


	/* Device management methods */
	virtual void setLocator(ILocator *locator) { this->locator = locator; }
	virtual void setVelocimeter(IVelocimeter *velocimeter) { this->velocimeter = velocimeter; }
	virtual void setAngularVelocimeter(IAngularVelocimeter *angvelocimeter) { this->angularVelocimeter = angvelocimeter; }



	/* Movement control methods */
	virtual Static getTarget() { return target; }

	/* Set a static to be the robot's target to move the robot. */
	virtual void setTarget(Static *target, float radius = 10,
						bool match_orientation = false) {
		this->target = target;
		acceptance_radius = radius;
	}

private:
	/* Devices */

	// Meters, locators and orientators
	ILocator *locator;
	IOrientator *orientator;
	IVelocimeter *velocimeter;
	IAngularVelocimeter *angularVelocimeter;

	// Actuators and drive system.
	IDriveSystem *drivesys;
	// ITempleBuildingClaw *claw;?

	float acceptance_radius;
	Static *target;
};

} /// END of namespace core
} /// END of namespace mew


#endif /* ROBOT_STATE_H_ */
