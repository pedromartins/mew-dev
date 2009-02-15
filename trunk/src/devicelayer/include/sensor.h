/*
 * sensor.h
 *
 *  Created on: 15-Feb-2009
 *      Author: Hok Shun Poon
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include <core.h>

using namespace mew::core;

namespace mew {
namespace perception {


/**
 * ILocator
 *
 * A locator is any means of providing a reasonable estimate of the robot's position.
 */
class ILocator {
	virtual ~ILocator() {}
	virtual Vector2df getLocation() = 0;
};

/**
 * IOrientator
 *
 * An orientator is any means of providing a reasonable estimate of the robot's orientation.
 */
class IOrientator {
	virtual ~IOrientator() {}
	virtual float getOrientation() = 0;
};

/**
 * IVelocimeter
 *
 * A velocimeter is any means of providing a reasonable estimate of the robot's current velocity.
 * NOTE that this is totally independent of what way the robot is facing.
 */
class IVelocimeter {
	virtual ~ISpedometer() {}
	virtual Vector2df getVelocity();
};

/**
 * IAngularVelocimeter
 *
 * An angular velocimeter is any means of getting a reasonable estimate of the robot's current angular velocity.
 */
class IAngularVelocimeter {
	virtual ~IAngularVelocimeter() {}
	virtual float getAngularVelocity() = 0;
};




} /// END of namespace perception
} /// END of namespace mew


#endif /* SENSOR_H_ */
