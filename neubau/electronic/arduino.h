#ifndef ARDUINOH
	#define ARDUINOH

#include "serial.h"


#define BAUDRATE 9600
#define LINTELSERVO 0

enum {SENSORS, CONTROL, ULTRASOUND, NUMOFARDUINOS}; //This list must agree with arduinoNames in arduino.cpp

class Arduino
{
public:
	Arduino();		//class constructor
	~Arduino();		//class destructor - takes care of closing all ttyUSB connections

	void init();	//initialise arduinos - this function sends a ? to ttyUSB0-2 and sorts the arduinos
			// into the arduino array, depending on how they reply; 's;' = sensors, 'c;' = servos (c for control), 'm;' = motor.

	//sensor acquiring functions
	void getIRreadings(int* buf);	//buf must be an array of 4 integers; this function returns the set of IR sensor values, each in cm.
	void getUSreadings(int* buf);	//buf must be an array of 2 integers; this function returns the set of Ultrasound sensor values, each in cm.
	int getCompassreading();	//returns the compass heading in "milli-degrees" (i.e. .1 of a degree)

	//servo control functions
	void dropLintel(); //Servo num defined above
	void resetLintel();

	
	//... todo: add them

private:
	bool checkConnection(int a);	//is an arduino connected? e.g. checkConnection(CONTROL);
	int arduino[NUMOFARDUINOS];		//file descriptors for our 3 arduinos
				// arduino[0] = sensor arduino
				// arduino[1] = servo arduino
				// arduino[2] = motor arduino

	//servo control functions
	void servos_setPos(char servoNum, int inAngle);
	void servos_setMax(int servoNum, int inNum);
	void servos_setMin(int servoNum, int inNum);

};

#endif
