/*
 * actuator.h
 *
 * Defines a actuator classes.
 * Actuators take in some velocity, and given a robot state
 * from the perception, it is able to drive the underlying
 * drive system.
 *
 *  Created on: 11-Feb-2009
 *      Author: fushunpoon
 */

#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include <vector2d.h>
#include <electronicinterface.h>
#include <perception.h>

using namespace mew::perception;

namespace mew {
namespace movement {

/**
 * Takes a velocity, and causes actuation, such that the robot
 * attempts to match the given velocity.
 */
class IActuator {
	virtual ~IActuator(){}
	virtual void actuateOutput(Vector2df velocity) = 0;
};



} /// END of namespace movement
} /// END of namespace mew

#endif /* SKID_STEER_ACTUATOR_H_ */
