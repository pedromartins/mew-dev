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

/**
 *
 */
class Context {
public:
	Context(IModel, StaticState);

};

/**
 * Robot
 *
 * Represents THIS single autonomous robot.
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

	/* Sets the current model to be something else entirely. */
	void setModel(IModel *model) { this->model = model; }
private:
	IModel *model;

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