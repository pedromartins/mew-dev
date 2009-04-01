/*
 * actuators.cpp
 *
 *  Created on: 01-Apr-2009
 *      Author: fushunpoon
 */

#include "actuator.h"

DriveSystem::DriveSystem() {
  init_comms(DEVICE_NODE);
}

DriveSystem::~DriveSystem(){
  end_comms();
}

void DriveSystem::setRawPowerLevel(motor_t motor, int raw_power_level) {
  write_byte_to_register(
			 WHEEL_MOTOR_CONTROLLER,
			 motor == LEFT ?
			 WHEEL_MOTOR_CONTROLLER_LEFT_SPEED:
			 WHEEL_MOTOR_CONTROLLER_RIGHT_SPEED,
			 raw_power_level);
}

