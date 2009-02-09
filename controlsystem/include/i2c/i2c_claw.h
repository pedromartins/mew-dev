#ifndef _I2C_CLAW_H
#define _I2C_CLAW_H

/*
 * Defines the interface to the i2c claw module that will be constructed
 * specifically for the function of building temples.
 *
 * All of these functions should be non-blocking.
 *
 *
 */


enum swipe_pos_t {
	INTERMEDIATE,
	SWIPE_LEFT,
	SWIPE_RIGHT
};

enum swipe_state_t {
	INTERMEDIATE,
	SWIPE_RETRACTED,
	SWIPE_EXTENDED
};

enum clamp_pos_t {
	INTERMEDIATE,
	CLAMP_FRONT,
	CLAMP_BACK
};

enum clamp_state_t {
	INTERMEDIATE,
	CLAMP_OPEN,
	CLAMP_CLOSED
};


swipe_state_t	get_swipe_state();
swipe_pos_t		get_swipe_pos();
clamp_state_t	get_clamp_state();
clamp_pos_t		get_clamp_pos();
int				get_jack_height();

/**
 * Sets the position of the swiper to be either left or right.
 * If the swiper is already in the position specifid by pos,
 * then nothing happens.
 *
 * @param side Can be either one of SWIPE_LEFT or SWIPE_RIGHT
 */
void set_swipe_pos(swipe_pos_t pos);

/**
 * Sets the state of the swiper to be either extended or not.
 * If the swiper is already in the position specified by state,
 * then nothing happens.
 *
 * @param state Can either be one of SWIPE_RETRACTED or SWIPE_EXTENDED
 */
void set_swipe_extended(swipe_state_t state)

/**
 * Sets the state of both clamps to be clamp_state.
 * If clamps are already in the state specified by clamp_state,
 * then this function does nothing.
 *
 * @param state Can be either one of CLAMP_OPEN or CLAMP_CLOSED
 */
void set_clamp_state(clamp_state_t state);


/**
 * Sets the position of both clamps to be clamp_position.
 * If the clamps aare already in the position specified by clamp_position,
 * then this function does nothing.
 *
 * @param clamp_position Can be either one of CLAMP_FRONT or CLAMP_BACK
 */
void set_clamp_position(clamp_pos_t pos);

/**
 * Sets how high the jack should be.
 * Moves from the present position into the new position immediately,
 *
 * @param mm
 */
void set_jack_height(int mm);

#endif
