#ifndef _I2C_MOTOR_H
#define _I2C_MOTOR_H

/*
 * Defines the software interface to the motor control hardware
 */

#define MOTOR_LEFT    0x01
#define MOTOR_RIGHT   0x02

void set_motor_speed(int motor, float rpm);

#endif