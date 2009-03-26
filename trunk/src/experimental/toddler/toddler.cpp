#include "../../electronic/interface/arduino.h"
#include "mew_i2c.h"
#include "serial.h"
#include <iostream>

#include <unistd.h>
#include <pthread.h>

using namespace std;

#define STATIONARY 127
#define MAX_FORWARD 195
#define MAX_BACKWARD 60

#define DEVICE_NODE "/dev/ttyUSB1"

bool keep_moving = true;
bool keep_turning = true;


// defines a structure for storing logical power levels.
struct power_level_t {
	int left_power_level;
	int right_power_level;
};

/**
 * Orientation
 *
 * A simple enumeration for a SimpleGridModel.
 * Logical north mayn't correspond to magnetic north.
 */
enum Orientation {
	NORTH, WEST, SOUTH, EAST
};

enum left_right_t {
	LEFT,
	RIGHT
};

// Power levels of both motors
power_level_t curr_pow = { STATIONARY, STATIONARY };

Arduino arduino;


void * interruptedMoveForwardProcedure(void *);
void * sensorThresholdInterruptor(void *p_threshold);
void interruptedTurnProcedure(left_right_t lr);
void compassTargetInterruptor(int orientation);

void driveForward(power_level_t *pl);
void driveBackward(power_level_t *pl);
void turnLeft(power_level_t *pl);
void turnRight(power_level_t *pl);

void stop(power_level_t *pl);

void setRawPowerLevel(left_right_t motor, int raw_power_level);
void updatePowerLevel(power_level_t *pl);

void initSerial();
void endSerial();

// GLOBAL threads.
pthread_t interruptor_thread;
pthread_t forward_thread;



int main()
{

	init_comms(DEVICE_NODE);

	//initialise arduino's
	arduino.init();
	sleep(2);

	int threshold = 30;

	pthread_create(&interruptor_thread, NULL, sensorThresholdInterruptor, (void *)threshold );
	pthread_create(&forward_thread, NULL, interruptedMoveForwardProcedure, (void *)NULL );

	pthread_join(forward_thread, NULL); // wait till it's done.

	stop(&curr_pow);
	updatePowerLevel(&curr_pow);

	end_comms();

	//read the compass like this:
	//cout << "Arduino: Compassheading: " << arduino.getCompassreading() << "; " << endl;


	/* Servo small test
	cout << "Resetting Lintel" << endl;
	ard.resetLintel();
	sleep(2);
	cout << "Setting Lintel" << endl;
	ard.dropLintel();
	sleep(2);
	cout << "Resetting Lintel" << endl;
	ard.resetLintel(); */

	return 0;
}



void * interruptedMoveForwardProcedure(void * blah) {
	while(keep_moving){
		driveForward(&curr_pow);
		updatePowerLevel(&curr_pow);

		usleep(100000);
	}
}

void interruptedTurnProcedure(left_right_t lr) {
	while(keep_turning) {
		if (lr == LEFT) {
			turnLeft(&curr_pow);
		} else {
			turnRight(&curr_pow);
		}
		updatePowerLevel(&curr_pow);
	}
}

/**
 * Interrupts the forward movement
 */
void * sensorThresholdInterruptor(void *p_threshold) {
	int ir[4];
	int threshold = (int)p_threshold;

	while(true) {
		//get the IR headings into an array like this:
		arduino.getIRreadings((int*)&ir);
		if(ir[0] > 0 && ir[0] < threshold) {
			keep_moving = false;
			cout << "STOPPING!!" << endl;
			break;
		}
	}
}

/**
 * Interrupts rotational movement
 */
void compassTargetInterruptor(int orientation) {

	arduino.getCompassreading();

	while(true) {
		keep_turning = false;
	}
}


/*********************************************
 * Power level and global state modifying functions
 *********************************************/

void driveForward(power_level_t *pl) {
	pl->left_power_level = MAX_FORWARD;
	pl->right_power_level = MAX_FORWARD;
}

void driveBackward(power_level_t *pl) {
	pl->left_power_level = MAX_BACKWARD;
	pl->right_power_level = MAX_BACKWARD;
}

void turnLeft(power_level_t *pl) {
	pl-> left_power_level = MAX_BACKWARD;
	pl-> right_power_level = MAX_FORWARD;
}

void turnRight(power_level_t *pl) {
	pl-> left_power_level = MAX_FORWARD;
	pl-> right_power_level = MAX_BACKWARD;
}


/**
 * Stops the robot.
 */
void stop(power_level_t *pl) {
	pl->left_power_level = STATIONARY;
	pl->right_power_level = STATIONARY;
}


/***************************
 * Low level things
 ***************************/

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
void setRawPowerLevel(left_right_t motor, int raw_power_level) {
	write_byte_to_register(
			WHEEL_MOTOR_CONTROLLER,
			motor == LEFT ?
					WHEEL_MOTOR_CONTROLLER_LEFT_SPEED:
			WHEEL_MOTOR_CONTROLLER_RIGHT_SPEED,
			raw_power_level);
}
