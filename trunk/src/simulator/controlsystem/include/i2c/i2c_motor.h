#ifndef _I2C_MOTOR_H
#define _I2C_MOTOR_H

/*
 * Defines the software interface to the motor control hardware
 */

enum motor_t {
	MOTOR_LEFT = 1,
	MOTOR_RIGHT
};


/**
 * Retrieves the current speed of the specified motor.
 *
 * @param motor The motor to query the speed for.
 * @return The speed of the motors in RPM.
 */
float get_motor_speed(motor_t motor);

/**
 * Sets and maintains the angular velocity of the motor specified by motor.
 *
 * @param motor Can be one of MOTOR_LEFT or MOTOR_RIGHT. Other motor numbers are allowed.
 * @param rpm	Revolutions per minute.
 */
void set_motor_speed(motor_t motor, float rpm);

#endif
