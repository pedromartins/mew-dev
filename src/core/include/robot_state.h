/*
 * robot_state.h
 *
 *  Created on: 15-Feb-2009
 *      Author: Hok Shun Poon
 */

#ifndef ROBOT_STATE_H_
#define ROBOT_STATE_H_

#include <core.h>

using namespace mew::core;

/**
 * Represents the state of the robot at any one time.
 */
struct RobotState {

	void update();
	Vector2dd pos;
	float orientation;
};


#endif /* ROBOT_STATE_H_ */
