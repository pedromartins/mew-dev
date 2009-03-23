#include "serial.h"
#include "sensors.h"

#include <iostream>

using namespace std;

int main()
{
	int arduino;
	arduino = serialport_init("/dev/ttyUSB0", 9600);

	IRreadings *irr = NULL;
	irr = getIRreadings(arduino);


	//sleep(1);

	cout << irr->ir0 << " " << irr->ir1 << " " << irr->ir2 << " " << irr->ir3 << endl;
	cout << getCompassreading(arduino) << endl;


	serialport_close(arduino);
	delete irr;

	return 0;
}

