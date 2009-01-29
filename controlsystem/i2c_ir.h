#ifndef _I2C_IR_H
#define _I2C_IR_H

/*
 * Defines the software interface to the IR module
 */

#define NORTH   0x01
#define EAST    0x02
#define SOUTH   0x03
#define WEST    0x04

//returns < 0 for undefined (ie, objects are too close or distance for accurate reading)
//return value is in mm
int get_ir_reading(int direction);

#endif