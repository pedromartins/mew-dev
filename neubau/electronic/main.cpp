#include "arduino.h"
#include <iostream>

using namespace std;

int main()
{
	//initialise arduino's
	Arduino ard;
	ard.init();

	//get the IR headings into an array like this:
	int ir[4] = {-1, -1, -1, -1};
	ard.getIRreadings(ir);
	cout << "Arduino: IR sensors: " << ir[0] << ", " << ir[1] << ", " << ir[2] << ", " << ir[3] << endl;
	sleep(1);
	ard.getIRreadings(ir);
	cout << "Arduino: IR sensors: " << ir[0] << ", " << ir[1] << ", " << ir[2] << ", " << ir[3] << endl;

	int us[2] = {-1, -1};
	ard.getUSreadings(us);
	cout << "Arduino: Ultrasound sensors: " << us[0] << ", " << us[1] << endl;

	//read the compass like this:
	cout << "Arduino: Compassheading: " << ard.getCompassreading() << "; " << endl;

	
	//Servo small test
	cout << "Resetting Lintel" << endl;
	ard.resetLintel();
	sleep(1);
	cout << "Setting Lintel" << endl;
	ard.dropLintel();
	sleep(1);
	cout << "Resetting Lintel" << endl;
	ard.resetLintel();

	return 0;
}

