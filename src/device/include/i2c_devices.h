/*
 * i2c_devices.h
 *
 * This file contains object-oriented wrappers for the i2c device API provided by the
 * electronicsinterface
 *
 *  Created on: 15-Feb-2009
 *      Author: Hok Shun Poon
 */

#ifndef I2C_DEVICES_H_
#define I2C_DEVICES_H_

#include "actuator.h"
#include "sensor.h"
#include <electronicinterface.h>

/**
 * I2CMotor
 *
 * Represents a I2CMotor with encoder.
 */
class I2CMotor : public IMotor {
public:
	I2CMotor(int motor_number) : id(motor_number){}

	bool hasEncoder() { return true; }
	float getRPM() { return get_motor_speed(id); }
	void setRPM(float rpm) { set_motor_speed(rpm); }
	float getMaxSpeed() {
		return get_motor_max_speed(id);
	}

	float getMaxAngularAcceleration() {
		return get_motor_max_angular_acceleration(id);
	}

private:
	int id;
};


/**
 * I2CCompass
 *
 * Represents a I2CCompass, from which you could get a reading of the orientation.
 */
class I2CCompass : public IOrientator {
public:

	I2CCompass(){}
	virtual ~I2CCompass(){};

	float getReading() { return get_compass_reading(); }
};


/**
 * TODO I2CInfrared(Array)
 */
class I2CInfrared {
public:
	I2CInfrared(ir_t direction):dir(direction){}
	virtual ~I2CInfrared(){};

	float getReading() { return get_ir_reading(dir); }
private:
	ir_t dir;
};

/**
 * TODO I2CUltrasound(Array)
 * Could be used as a ILocator.
 */
class I2CUltrasound {
public:
	I2CUltrasound(ultrasound_t direction): dir(direction) {}
	virtual ~I2CInfrared(){};

	float getReading() { return get_ultrasound_reading(dir); }
private:
	ultrasound_t dir;
};

/**
 * TODO I2CClaw
 * Provide useful high-level functions.
 */
class I2CClaw {
public:
	I2CClaw(){}
	virtual ~I2CInfrared(){};

private:
};


#endif /* I2C_DEVICES_H_ */
