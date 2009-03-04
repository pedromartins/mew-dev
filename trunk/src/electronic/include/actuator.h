/*
 * actuator.h
 *
 *
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#ifndef ACTUATOR_H_
#define ACTUATOR_H_

/**
 * IMotor
 *
 * Represents a motor with or without an encoder.
 */
class IMotor {
	virtual ~IMotor();
	virtual bool hasEncoder();
	virtual float getRPM();
	virtual void setRPM(float rpm);
};

/**
 * IServo
 *
 * Represents a servomotor.
 */
class IServo {
	virtual ~IServo();
	virtual float getAngle();
	virtual void setAngle();
};



#endif /* ACTUATOR_H_ */
