#ifndef __MEW_I2C_H
#define __MEW_I2C_H

#include <stdint.h>

#define DRIVE_MOTOR_DEVICE_NODE "/dev/ttyUSB0"

/*******************************
 *usb-i2c serial module commands
 *******************************/

//send single byte to device without addressable registers
#define I2C_SGL 0x53

//write a single byte to an internal register
#define I2C_CMD 0x55

//read multiple bytes from a device without addressable registers
#define I2C_MUL 0x54

/*************************
 *mew_i2c device addresses
 *************************/

//should these be 7 or eight bits?
//this is 7 bit atm
//the test servo controller (an arduino)

#define MEW_DEV_SERVO_TEST 0x0F
#define MEW_DEV_ARDUINO_01 0x0E

//this is 8 bit atm
#define WHEEL_MOTOR_CONTROLLER 0xB0

#define COMPASS 0x21

/*************************
 *mew_i2c device registers
 *************************/

#define WHEEL_MOTOR_CONTROLLER_LEFT_SPEED 0x01
#define WHEEL_MOTOR_CONTROLLER_RIGHT_SPEED 0x02

/*
 * Must be called only once before any communications
 * Returns 1 on success, <0 on error
 */
void init_comms(const char* device_node);

/*
 * Must be called only once at the very end of all communications
 * Returns 1 on success, <0 on error
 */
void end_comms();

/*
 * Send one byte to a device (no internal registers yet)
 */
void send_byte(int addr, char byte_to_send);

/*
 * Write one byte to a device WITH internal registers!
 */
void write_byte_to_register(int addr, int reg, char command);

/*
 * Read multiple bytes from a device (not internal registers)
 */
void read_bytes(uint8_t addr, uint8_t bytes, void * retbuf);

#endif
