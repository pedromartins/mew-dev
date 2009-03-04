/*
 * BasicRobot.h
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#ifndef BASICROBOT_H_
#define BASICROBOT_H_

#include <entity.h>

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
class BasicRobot : public Entity {
	/**
	 * Initializes the robot at a particular location
	 * in the given 2D grid-based model.
	 */
	BasicRobot(GridModel *model, Vector2di initial_loc, Orientation orientation);
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
	GridModel *getModel() {
		return model;
	}
	void setModel(GridModel *model) {
		this->model = model;
	}
private:
	GridModel *model; // the current world model used.
};


#endif /* BASICROBOT_H_ */
