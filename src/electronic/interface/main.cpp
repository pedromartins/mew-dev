#include "arduino.h"

#include <iostream>

using namespace std;

int main()
{
	Arduino ard;
	ard.init();

	int ir[4];
	ard.getIRreadings((int*)&ir);

	cout << "Arduino: Compassheading: " << ard.getCompassreading() << "; IR ranges: ";
	//cout << irr.ir0 << ", " << irr.ir1 << ", " << irr.ir2 << ", " << irr.ir3 << endl;

	return 0;
}

