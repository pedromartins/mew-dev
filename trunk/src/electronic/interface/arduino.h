#ifndef ARDUINOH
	#define ARDUINOH

#include "serial.h"
#include "sensors.h"

class Arduino
{
public:
	Arduino();		//class initialisations
	~Arduino();
	void init();			//initialise arduinos

	//sensor acquiring functions
	void getIRreadings(int* buf);
	int getCompassreading();

private:
	int arduino[3];		//file descriptors for our 3 arduinos

};

#endif
