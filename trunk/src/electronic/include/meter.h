/*
 * meter.h
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#ifndef METER_H_
#define METER_H_


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



#endif /* METER_H_ */
