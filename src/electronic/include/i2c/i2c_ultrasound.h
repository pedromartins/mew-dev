#ifndef _I2C_ULTRASOUND_H
#define _I2C_ULTRASOUND_H

/*
 * Defines the software interface to the sonar (ultrasound) module
 */

enum ultrasound_t {
	NORTH = 1,
	EAST,
	SOUTH,
	WEST
};

/**
 * Returns < 0 for undefined (ie, objects are too close or distance for accurate reading)
 * return value is in mm
 **/
int get_ultrasound_reading(ultrasound_t direction);

#endif
