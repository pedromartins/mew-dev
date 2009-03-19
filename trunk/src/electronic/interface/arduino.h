#ifndef ARDUINOH
	#define ARDUINOH

#include "serial.h"

class Arduino
{
public:
	Arduino();		//class constructor
	~Arduino();		//class destructor - takes care of closing all ttyUSB connections

	void init();	//initialise arduinos - this function sends a ? to ttyUSB0-2 and sorts the arduinos
			// into the arduino array, depending on how they reply; 's;' = sensors, 'c;' = servos (c for control), 'm;' = motor.

	//sensor acquiring functions
	void getIRreadings(int* buf);	//buf must be an array of 4 integers; this function returns the set of IR sensor values, each in cm.
	int getCompassreading();	//returns the compass heading in "milli-degrees" (i.e. .1 of a degree)

	//servo control functions
	//... todo: add them

private:
	int arduino[3];		//file descriptors for our 3 arduinos
				// arduino[0] = sensor arduino
				// arduino[1] = servo arduino
				// arduino[2] = motor arduino

};

#endif
