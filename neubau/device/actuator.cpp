/*
 * actuator.cpp
 *
 *  Created on: 01-Apr-2009
 *      Author: fushunpoon
 */

#include "actuator.h"

#include <iostream>

using namespace std;

/*
DriveSystem::DriveSystem() {
	init_comms(DEVICE_NODE);
}

DriveSystem::~DriveSystem(){
	end_comms();
}

void DriveSystem::setPowerLevel(float powerlevel, float ratio){
	float left_power_level;
	float right_power_level;

	if (ratio > 0) {
		left_power_level = powerlevel;
		right_power_level = powerlevel*(1-2*ratio);
	} else {
		left_power_level = powerlevel*(2*ratio+1);
		right_power_level = powerlevel;
	}

	setRawPowerLevel(DriveSystem::LEFT, (int)((powerlevel+1)*127.5));
	setRawPowerLevel(DriveSystem::RIGHT, (int)((powerlevel+1)*127.5));
}

void DriveSystem::setRawPowerLevel(motor_t motor, int raw_power_level) {
	write_byte_to_register(
			WHEEL_MOTOR_CONTROLLER,
			motor == DriveSystem::LEFT ?
					WHEEL_MOTOR_CONTROLLER_LEFT_SPEED:
			WHEEL_MOTOR_CONTROLLER_RIGHT_SPEED,
			raw_power_level);
}
*/

void SimpleDifferentialDrive::moveForward(int squares) {
	/// TODO! Might look like the code above, but I don't know how
	/// you might want to measure the distance of squares.
	cerr << "Not implemented!!!" << endl;
}

void SimpleDifferentialDrive::turn(TurnDirection dir) {
	/// TODO!
	cerr << "Not implemented!!!" << endl;
}
