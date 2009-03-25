/* toddles.cpp
 *
 * A test program to drive some motors on the robot;
 *
 * Based on an example which shows us how to use the mew_i2c library!
 * gcc -o mew_i2c_demo mew_i2c.c mew_i2c_demo.c
 */

//to initalise the library we need to know the device node
//for the usb-i2c device
//if this is the only device plugged in then it's probably
// "/dev/ttyUSB0"
//you can just grep /dev and have a look!

#define DEVICE_NODE "/dev/ttyUSB1"
#define ARDUINO_NODE "/dev/ttyUSB0"

#define KEY_ESC 27
#define KEY_J 106
#define KEY_I 105
#define KEY_F 102
#define KEY_R 114
#define KEY_Q 113
#define KEY_SPACE 32

#define STATIONARY 127
#define MAX_FORWARD 195
#define MAX_BACKWARD 60

#include <unistd.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <signal.h>
#include "mew_i2c.h"
#include "serial.h"
#include "sensors.h"


using namespace std;


/**
 * Orientation
 *
 * A simple enumeration for a SimpleGridModel.
 * Logical north mayn't correspond to magnetic north.
 */
enum Orientation {
	NORTH, WEST, SOUTH, EAST
};

enum motor_t {
	LEFT,
	RIGHT
};

// defines a structure for storing logical power levels.
struct power_level_t {
	int left_power_level;
	int right_power_level;
};

/**
 * Forward class declarations for 'Programs'
 */
class Program;
class ForwardAndStopProgram;
class NavigateAroundObstacleProgram;
class RemoteCVControlledProgram;

void initCV();
void endCV();

void initSerial();
void endSerial();

void initProgram(); // what program should the robot run?
void endProgram();  // program cleanup code...

void loop();
void findkey();

void onLeftTrackbarMove(int val);
void onRightTrackbarMove(int val);
void onRunStraightLineProgram(int val);
void setRawPowerLevel(motor_t motor, int raw_power_level);
void terminationHandler(int signum);

void updateCVImage();
void updateTrackbars(power_level_t *pl);
void updatePowerLevel(power_level_t *pl);

void driveForward(power_level_t *pl);
void driveBackward(power_level_t *pl);
void turnLeft(power_level_t *pl);
void turnRight(power_level_t *pl);
void stop(power_level_t *pl);
void truncate_power_level(power_level_t *pl);
void sensorInterruption(power_level_t *pl);

void handleEmergencyStopButton(power_level_t *pl);
void handleCVKeyPresses(power_level_t *pl);


// Power levels of both motors
power_level_t curr_pow = { STATIONARY, STATIONARY };



/**************************
 * Robot State information
 **************************/
Program *prog;

// whether we are running the loop
bool loop_running = true;

// robot state
// Vector2di pos;
// Orientation ori;
int ori_off = 0; // clockwise offset of 'logical north' from magnetic north.

// The arduino ID
int arduino;


CvCapture *cam;
IplImage *image;
IplImage *smaller;


/*********************************************
 * Life-cycle functions
 *********************************************/

int main(void){
	signal(SIGINT, terminationHandler);

	init_comms(DEVICE_NODE);
	initCV(); // initializes CV
	initSerial();


	updatePowerLevel(&curr_pow);

	loop();


	endSerial();
	endCV();
	end_comms();
	//findkey();
}


void initSerial() {
	IRreadings *irr = NULL;
	arduino = serialport_init(ARDUINO_NODE, 9600);
}

/**
 *
 */
void initCV() {
	cvNamedWindow("Driving",CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar("Left", "Driving", &(curr_pow.left_power_level), 255, &onLeftTrackbarMove);
	cvCreateTrackbar("Right","Driving", &(curr_pow.right_power_level), 255, &onRightTrackbarMove);
	cvCreateTrackbar("Run", "Driving", &straight_line_program, 1, &onRunStraightLineProgram);
	cam = cvCreateCameraCapture(0);
	smaller = cvCreateImage(cvSize(160,120), 8,3);
}

void endCV(){
	cvDestroyAllWindows();
}

void endSerial(){
	serialport_close(arduino);
}


/**
 * This is the main loop of the robot system.
 *
 * 0.1: This loop handled keypresses to control motor power levels
 * 		and displayed the image on the camera.
 * 0.2: This loop should, on execution, make the robot move forwards
 * 		until its IR sensor finds an obstacle, at which point it stops.
 *
 */
void loop() {

	while( loop_running ){
		// update the webcam image.
		updateCVImage();

		program->run();

		// update the trackbars to reflect updated curr_pows.
		updateTrackbars(&curr_pow);

		// send the new power levels.
		updatePowerLevel(&curr_pow);

	}

}

class Program {
	void run() = 0;
};

/**
 * Makes the robot drive forward and when the sensor detects something in front
 * it stops the robot entirely.
 */
class ForwardAndStopProgram : public Program {
	void run() {
		driveForward(&curr_pow); // the actual program output.
		sensorInterruption(&curr_pow); // if the sensor detects something, stop.
		handleEmergencyStopButton(&curr_pow); // overriding stopping power level.
	}
}

class RemoteCVControlledProgram : public Program {
	void run() {
		handleCVKeyPresses(&curr_pow);
	}
};

/**
 * This program rotates the robot around right 90 degrees, moves a pre-defined
 * amount left, moves a certain amount
 *
 * Effectively, this navigates the robot using simple movements around a rectangular
 * area.
 */
class NavigateAroundObstacleProgram : public Program {
	void run() {
		handleCVKeyPresses(&curr_pow);
	}
};

/*********************************************
 * Helper functions
 *********************************************/

void terminationHandler(int signum) {
	stop(&curr_pow);
	updatePowerLevel(&curr_pow);

	endCV();
	end_comms();
	cout<< "Dying nicely...! :(" << endl;
	exit(1);
}


void updateCVImage() {
	image = cvQueryFrame(cam);
	cvResize(image,smaller);
	cvShowImage("Driving",smaller);
}

void findkey() {
	int c = 0;
	while(true) {
		 c = cvWaitKey(0);
		 cout << c << endl;
	}
}

void updateTrackbars(power_level_t *pl) {
	cvSetTrackbarPos("Left","Driving",pl->left_power_level);
	cvSetTrackbarPos("Right","Driving",pl->right_power_level);
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

/**
 * When the emergency stop button is pressed, return to key listener
 * mode.
 */
void handleEmergencyStopButton(power_level_t *pl){
	int c = 0;
	c = cvWaitKey(400);

	switch(c) {
	case KEY_SPACE:
		stop(&curr_pow);
		straight_line_program = false; // stop program from running.
		break;
	}

}

/**
 * For use with loop version 0.1
 *
 * Pass in a power level and it would be appropriately changed.
 */
void handleCVKeyPresses(power_level_t *pl) {
	int c = 0;
	c = cvWaitKey(500);

	switch (c) {
	case KEY_I:
		pl->right_power_level -= 4;
		break;
	case KEY_J:
		pl->right_power_level += 4;
		break;
	case KEY_F:
		pl->left_power_level -= 4;
		break;
	case KEY_R:
		pl->left_power_level += 4;
		break;
	case KEY_SPACE:
		stop(pl);
		break;
	case KEY_ESC:
		loop_running = false;
		break;
	}

	truncate_power_level(pl);
}

/**
 * Ensures that the input power level is within range.
 * Truncates outlying values to the nearest extreme.
 */
void truncate_power_level(power_level_t *pl) {
	if (pl->left_power_level < MAX_BACKWARD) {
		pl->left_power_level = MAX_BACKWARD;
	} else if( pl->left_power_level > MAX_FORWARD) {
		pl->left_power_level = MAX_FORWARD;
	}
	if (pl->right_power_level < MAX_BACKWARD) {
		pl->right_power_level = MAX_BACKWARD;
	} else if( pl->right_power_level > MAX_FORWARD) {
		pl->right_power_level = MAX_FORWARD;
	}
}

/**
 * Stops the robot if the sensors have sensed some sort of obstruction.
 */
void sensorInterruption(power_level_t *pl){
	// TODO: do something meaningful with sensors

	// namely stop the program.
	IRreadings *irr = getIRreadings(arduino);

	//sleep(1)
	if (irr->ir0 < 30) {
		stop(pl);
		straight_line_program = false;
	}

	// cout <<  << " " << irr->ir1 << " " << irr->ir2 << " " << irr->ir3 << endl;
	// cout << getCompassreading(arduino) << endl;

	delete irr;
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
void setRawPowerLevel(motor_t motor, int raw_power_level) {
	write_byte_to_register(
			WHEEL_MOTOR_CONTROLLER,
			motor == LEFT ?
			WHEEL_MOTOR_CONTROLLER_LEFT_SPEED:
			WHEEL_MOTOR_CONTROLLER_RIGHT_SPEED,
			raw_power_level);
}


/***********************
 * EVENT HANDLERS
 **********************/

// mainly for trackbars.
void onLeftTrackbarMove(int val) {
	curr_pow.left_power_level = val;
}

void onRightTrackbarMove(int val) {
	curr_pow.right_power_level = val;
}

// turns the program running on or off.
void onRunStraightLineProgram(int val) {
	// TODO abstract out the notion of a program.
	// nasty boolean int conversion.
	straight_line_program = val;
}
