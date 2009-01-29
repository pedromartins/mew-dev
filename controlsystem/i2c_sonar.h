#ifndef _I2C_SONAR_H
#define _I2C_SONAR_H

/*
 * Defines the software interface to the sonar module
 */

#define NORTH   0x01
#define EAST    0x02
#define SOUTH   0x03
#define WEST    0x04

//returns < 0 for undefined (ie, objects are too close or distance for accurate reading)
//return value is in mm
int get_sonar_reading(int direction);

#endif