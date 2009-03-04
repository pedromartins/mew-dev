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
