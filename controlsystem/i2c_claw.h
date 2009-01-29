#ifndef _I2C_CLAW_H
#define _I2C_CLAW_H

/*
 * Defines the software interface to the sonar module
 */

#define SWIPE_LEFT            0x01
#define SWIPE_RIGHT           0x02

#define CLAMP_OPEN            0x03
#define CLAMP_CLOSED          0x04

#define CLAMP_MOVE_FORWARD    0x05
#define CLAMP_MOVE_BACKWARD   0x06


//moves the swiper to the left or right
void set_swipe(int side);

//opens or closes both clamps together
void set_clamp_state(int clamp_state);

//moves the clamps backwards or forwards
void set_clamp_position(int clamp_position);

void set_jack_height(int mm);

#endif