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

/**
 * Takes a velocity, and causes actuation, such that the robot
 * attempts to match the given velocity.
 */
class IActuator {
	virtual ~IActuator(){}
	virtual void actuateOutput(Vector2df velocity) = 0;
};

/**
 * Takes a velocity, and gives the output velocity of the
 *
 */
class ISkidSteerBehaviour {

	virtual ~ISkidSteerBehaviour();
	virtual float getLeftMotorSpeed() = 0;
	virtual float getRightMotorSpeed() = 0;

}


class SkidSteerActuator : public IActuator {
public:

	// Creates a SkidSteerActuator with appropriate weights.
	SkidSteerActuator();
	virtual ~SkidSteerActuator();

	/**
	 * Actuate both motors.
	 *
	 * */
	virtual void actuateOutput(Vector2df velocity);

private:


};


/**
 * SkidSteerTurningBehaviour
 *
 * Produces appropriate acceleration request
 */

class SkidSteerTurningBehaviour {
public:

	double getSpeed();
private:

};


/**
 * SkidSteerDriveBehaviour
 *
 * Produces appropriate acceleration request
 */
class SkidSteerDriveBehaviour {
public:

private:

};

#endif /* SKID_STEER_ACTUATOR_H_ */
