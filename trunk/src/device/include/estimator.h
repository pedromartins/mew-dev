/*
 * estimator.h
 *
 * Estimates the internal state of the robot.
 *
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#ifndef ESTIMATOR_H_
#define ESTIMATOR_H_

/**
 * ILocator
 *
 * A locator is any means of providing a reasonable estimate of the robot's position.
 * This template allows any type of vector.
 */
template <typename T>
class ILocator {
	virtual ~ILocator() {}
	virtual Vector2d<T> getLocation() = 0;
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

#endif /* ESTIMATOR_H_ */
