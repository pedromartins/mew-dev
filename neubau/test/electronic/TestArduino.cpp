#include <electronic/arduino.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main (int argc, char **argv)
{
	int IRVals[4];

	arduino_t ourArds;
	if(ourArds.open(SENSORS) == 0)
	{
		ourArds.debugVal = 4;
		ourArds.setCompassHandler();
		while(1) {
			usleep(100000);
			cout << "Compass heading is " << ourArds.getBigHeading() << endl;
		}
	}
	return 0;
}
