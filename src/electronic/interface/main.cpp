#include "arduino.h"
#include <iostream>

using namespace std;

int main()
{
	//initialise arduino's
	Arduino ard;
	ard.init();

	//get the IR headings into an array like this:
	int ir[4];
	ard.getIRreadings((int*)&ir);
	cout << "Arduino: IR sensors: " << ir[0] << ", " << ir[1] << ", " << ir[2] << ", " << ir[3] << endl;

	int us[2];
	ard.getUSreadings((int*)&us);
	cout << "Arduino: Ultrasound sensors: " << us[0] << ", " << us[1] << endl;

	//read the compass like this:
	cout << "Arduino: Compassheading: " << ard.getCompassreading() << "; " << endl;

	return 0;
}

