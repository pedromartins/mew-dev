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
 * A basic robot must be able to support basic functions
 * such as:
 *
 * - getting its own position
 * - moving forward
 * - turning left and right.
 * - stopping.
 * - picking something up with its claw.
 *
 *
 */

class BasicRobot {
	/**
	 * Initializes the robot at a particular location
	 * in the given 2D grid-based model.
	 */
	BasicRobot(IGridModel *model, Vector2di location);

	// Move the robot forward one grid square.
	virtual void moveForward() = 0;

	// Pick up what's in *front* of the robot.
	virtual void pickUp() = 0;

	/**
	 * Turns the robot 45º left if left is TRUE,
	 * otherwise turns the robot 45º right.
	 * @param left iff TRUE, will turn robot left, else will turn robot right.
	 */
	void turn(turn_direction_t left);

	// Get position from the sensors
	Vector2di getPosition();

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

private:

	// These meters should provide the most accurate readings possible to the robot's internal state.
	IVelocimeter *velocimeter;
	IAngularVelocimeter *angularVelocimeter;

};

/**
 * TempleBuildingRobot
 *
 *
 */
class TempleBuildingRobot : public IRobot {
public:
	TempleBuildingRobot(IModel *model, StaticState initial_state);
	virtual ~TempleBuildingRobot();
private:

};


} /// END of namespace core
} /// END of namespace mew


#endif /* ROBOT_STATE_H_ */
