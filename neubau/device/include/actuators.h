/*
 * actuators.h
 *
 *  Created on: 01-Apr-2009
 *      Author: fushunpoon
 */

#ifndef ACTUATORS_H_
#define ACTUATORS_H_

#include "mew-i2c.h"

class DriveSystem {
public:
	DriveSystem() {
		init_comms();
	}
	virtual ~DriveSystem();


	enum motor_t {
		LEFT,
		RIGHT
	};

	/**
	 * powerlevel ranges from -1 to 1
	 * ratio ranges from -1 to 1 also.
	 */
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


	/**
	 * Updates the motors' raw power level based on the given logical
	 * power level.
	 */
	void updatePowerLevel(power_level_t *pl) {
		setRawPowerLevel(LEFT, pl->left_power_level);
		setRawPowerLevel(RIGHT, pl->right_power_level);
	}

	/**
	 * setRawPowerLevel
	 *
	 * Sends out a byte to the mew-i2c motors. This is a raw power level.
	 */
	void setRawPowerLevel(motor_t motor, int raw_power_level) {
		write_byte_to_register(
				WHEEL_MOTOR_CONTROLLER,
				motor == LEFT ?
				WHEEL_MOTOR_CONTROLLER_LEFT_SPEED:
				WHEEL_MOTOR_CONTROLLER_RIGHT_SPEED,
				raw_power_level);
	}
private:
};




#endif /* ACTUATORS_H_ */
