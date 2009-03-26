#include "serial.h"
#include "sensors.h"
#include "string.h"//memset..lolz
#include <sstream>
#include <iostream>//debug
#include <unistd.h>
#include <stdlib.h>

using namespace std;

IRreadings* getIRreadings(int arduino_fd)
{
	IRreadings * irr = new IRreadings;

	char buf[128];
	memset(&buf, 0, 128);

	if(serialport_write(arduino_fd, "i;\n") == -1)
		cout << "ERROR";

	usleep(50000);
	serialport_read_until(arduino_fd, (char*)&buf, ';');

	istringstream iss (buf);

	int vals[4] = {0,0,0,0};

	for(int i = 0; i < 4; i++)
	{
		iss >> vals[i];
	}

	irr->ir0 = vals[0];
	irr->ir1 = vals[1];
	irr->ir2 = vals[2];
	irr->ir3 = vals[3];

	return irr;
}

int getCompassreading(int arduino_fd)
{
	char buf[128];
	memset(&buf, 0, 128);

	if(serialport_write(arduino_fd, "c;\n") == -1)
		cout << "ERROR";

	usleep(50000);
	serialport_read_until(arduino_fd, (char*)&buf, ';');

	int reading = atoi((char*)&buf);
	if(reading == 0 || buf == "0")
		return -1;

	return reading;
}
