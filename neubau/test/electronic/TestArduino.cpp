#include <electronic/arduino.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main (int argc, char **argv)
{
	int IRVals[4];

	ArduinoManager ourArds;
	if(ourArds.open(SENSORS))
	{
		// FIXME dude, that is insane. Looping forever in a unit test?!
		while(1) {
			usleep(100000);
			cout << "Compass heading is " << ourArds.getBigHeading() << endl;
		}
	}
	cout << "TestArduino: Skipping test as complete..." << endl;
	return 0;
}
