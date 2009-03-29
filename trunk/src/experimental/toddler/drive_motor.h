#ifndef __DRIVE_MOTOR_H
#define __DRIVE_MOTOR_H

/*
 * Some basic motor speeds
 */

#define FULL_FORWARDS 255;
#define HALF_FORWARDS 192;
#define STOP 127;
#define HALF_BACKWARDS 64;
#define FULL_BACKWARDS 0;

void init_drive_motor();
void destroy_drive_motor();

void left_motor_power(int power_level);
void right_motor_power(int power_level);

#endif __DRIVE_MOTOR_H
