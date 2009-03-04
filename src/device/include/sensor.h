/*
 * sensor.h
 *
 *  Created on: 15-Feb-2009
 *      Author: Hok Shun Poon
 */

#ifndef SENSOR_H_
#define SENSOR_H_

/*
 * This is messy, but it saves a function call or code duplication.
 */
#define EULER_INTEGRATION(duration, velocity, rotation) \
    position.x += (velocity).x*duration; \
    position.y += (velocity).y*duration; \
    orientation += (rotation)*duration; \
    orientation = real_mod_real(orientation, M_2PI);

/*
 * Kinematic datatype, it is capable of completing
 * Beeman integration. Error terms are ignored. NOTE: not done for orientation/rotations.
 */
#define BEEMAN_INTEGRATION(duration, position, velocity, newAcceleration, acceleration, oldAcceleration) \
	position.x += velocity.x*duration + (2*acceleration.x*duration*duration)/3 \
					- (oldAcceleration.x*duration*duration)/6; \
	position.y += veloctiy.y*duration + (2*acceleration.x*duration*duration)/3 \
					- (oldAcceleration.y*duration*duration)/6; \
	oldVelocity = velocity; \
	velocity.x += (newAcceleration.x*duration)/3 + (5*acceleration.x*duration)/6 \
					- (oldAcceleration.x*duration)/6; \
	velocity.y += (newAcceleration.y*duration)/3 + (5*acceleration.y*duration)/6 \
					- (oldAcceleration.y*duration)/6; \
	oldAccleration = accleration; \
	acceleration = newAcceleration


#include <core.h>
#include "actuator.h"

using namespace mew::core;

namespace mew {
namespace perception {



/**
 * DifferentialOdometricLocator
 *
 * Uses odometry to provide an estimate of the location at the
 * current time.
 * This is done by keeping track of old kinematic values.
 */
class DifferentialOdometricLocator : public ILocator {
public:
	DifferentialOdometricLocator(DifferentialDriveSystem *drivesys)
	: drivesys(drivesys) {

	}

private:
	DifferentialDriveSystem * drivesys;
};

/**
 * DifferntialOdometricOrientator
 *
 * Uses odometry
 */
class DifferentialOdometricOrientator : public IOrientator {
public:
	DifferentialOdometricOrientator(DifferentialDriveSystem *drivesys)
	: drivesys(drivesys){

	}
private:
	DifferentialDriveSystem *drivesys;
};


} /// END of namespace perception
} /// END of namespace mew


#endif /* SENSOR_H_ */
