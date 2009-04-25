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
		// TODO make a real unit test!
		for(int i=0;i<10;i++) { 
			usleep(100000);
			cout << "Compass heading is " << ourArds.getBigHeading() << endl;
		}
	}
	cout << "TestArduino: Skipping test as complete..." << endl;
	return 0;
}
