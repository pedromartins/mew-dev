/*
 * actuators.h
 *
 *  Created on: 01-Apr-2009
 *      Author: fushunpoon
 */

#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#define DEVICE_NODE "/dev/ttyUSB1"

class DriveSystem {
public:
	DriveSystem();
	~DriveSystem();

	enum motor_t {
		LEFT,
		RIGHT
	};

	void inline stop() {
		setPowerLevel(0.0,0.0);
	}

	/**
	 * powerlevel ranges from -1 to 1
	 * ratio ranges from -1 to 1 also.
	 */
	void setPowerLevel(float powerlevel, float ratio);

	/**
	 * setRawPowerLevel
	 *
	 * Sends out a byte to the mew-i2c motors. This is a raw power level.
	 */
	void setRawPowerLevel(motor_t motor, int raw_power_level);

private:
};




#endif /* ACTUATORS_H_ */
