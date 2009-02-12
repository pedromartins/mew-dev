#ifndef _I2C_IR_H
#define _I2C_IR_H

/*
 * Defines the software interface to the IR module
 */

enum ir_t {
	NORTH = 1,
	EAST,
	SOUTH,
	WEST
};


/**
 * Get an ir reading the specified direction.
 * Returns < 0 for undefined (ie, objects are too close or distance for accurate reading)
 *
 * @param direction Can be one of NORTH, EAST, SOUTH, WEST.
 * @return
 */
int get_ir_reading(ir_t direction);

#endif
