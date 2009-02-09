#ifndef _I2C_SONAR_H
#define _I2C_SONAR_H

/*
 * Defines the software interface to the sonar module
 */

enum sonar_t {
	NORTH = 1,
	EAST,
	SOUTH,
	WEST
};

/**
 * Returns < 0 for undefined (ie, objects are too close or distance for accurate reading)
 * return value is in mm
 **/
int get_sonar_reading(sonar_t direction);

#endif
