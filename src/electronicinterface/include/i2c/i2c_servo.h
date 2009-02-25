/*
 * i2c_servo.h
 *
 *  Created on: 15-Feb-2009
 *      Author: Hok Shun Poon
 */

#ifndef I2C_SERVO_H_
#define I2C_SERVO_H_

/**
 * Optional implementation
 * Do we really really want direct control?
 */

float get_angle(int servo_id);

void set_angle(int servo_id, float angle);

float get_max_angle(int servo_id);
float get_min_angle(int servo_id);

#endif /* I2C_SERVO_H_ */
