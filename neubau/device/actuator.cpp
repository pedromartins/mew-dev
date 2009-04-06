/*
 * actuators.cpp
 *
 *  Created on: 01-Apr-2009
 *      Author: fushunpoon
 */

#include "actuator.h"

#include <electronic/mew_i2c.h>

DriveSystem::DriveSystem() {
	init_comms(DEVICE_NODE);
}

DriveSystem::~DriveSystem(){
	end_comms();
}

void setPowerLevel(float powerlevel, float ratio){
	float left_power_level;
	float right_power_level;

	if (ratio > 0) {
		left_power_level = powerlevel;
		right_power_level = powerlevel*(1-2*ratio);
	} else {
		left_power_level = powerlevel*(2*ratio+1);
		right_power_level = powerlevel;
	}

	setRawPowerLevel(LEFT, (int)((powerlevel+1)*127.5));
	setRawPowerLevel(RIGHT, (int)((powerlevel+1)*127.5));
}

void DriveSystem::setRawPowerLevel(motor_t motor, int raw_power_level) {
	write_byte_to_register(
			WHEEL_MOTOR_CONTROLLER,
			motor == LEFT ?
					WHEEL_MOTOR_CONTROLLER_LEFT_SPEED:
			WHEEL_MOTOR_CONTROLLER_RIGHT_SPEED,
			raw_power_level);
}

