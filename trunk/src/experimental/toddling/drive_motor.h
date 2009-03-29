#ifndef __DRIVE_MOTOR_H
#define __DRIVE_MOTOR_H

/*
 * Some basic motor speeds
 */

#define FULL_FORWARDS 255
#define HALF_FORWARDS 192
#define STOP 127
#define HALF_BACKWARDS 64
#define FULL_BACKWARDS 0

#define MOTOR_DEVICE_NODE "/dev/ttyUSB0"

void init_drive_motor();
void destroy_drive_motor();

void set_drive_motor_power(int left_power_level, int right_power_level);

#endif
