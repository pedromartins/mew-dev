#include "arduino.h"
#include <unistd.h>
#include <iostream>

using namespace std;

int main (int argc, char **argv)
{
	int IRVals[4];

	Arduinos ourArds;
	ourArds.open(SENSORS);

	while(1) {
	ourArds.getIR(IRVals);

	for(int i = 0; i < 4; i++) 
		cout << IRVals[i] << " ";
	cout << ourArds.getCompass();
	cout << endl;

	usleep(100000);
	}
	return 0;
}

