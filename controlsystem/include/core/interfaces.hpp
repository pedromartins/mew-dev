/*
 * interfaces.hpp
 *
 *  Created on: 03-Feb-2009
 *      Author: fushunpoon
 */

#ifndef INTERFACES_HPP_
#define INTERFACES_HPP_

/*
 * Interface classes
 *
 * Here are definitions of some required interfaces for the control
 * system of the robot.
 *
 * Interface classes themselves should never have an implementation,
 * because they should never be instanticated, nor do they have any
 * actual methods. All methods are pure virtual, so that implementing
 * classes are obliged to override the functionality promised here.
 *
 * Design decision: Use templates for types????
 *
 * See Java Interfaces.
 */


/**
 * Can give an estimated reading of a robot's new location.
 */
class ILocator {
	virtual Point2df getLocation() = 0;
};

/**
 * Can give an estimated reading of a robot's new orientation.
 */
class IOrientator {
	virtual float getOrientation() = 0;
};

/**
 * Can give an estimated reading of a robot's speed.
 */
class ISpedometer {
	virtual float getSpeed() = 0;
};

/**
 * Can give an estimated reading of a robot's angular velocity.
 */
class IAngularVelocimeter {
	virtual float getAngularVelocity() = 0;
};


#endif /* INTERFACES_HPP_ */
