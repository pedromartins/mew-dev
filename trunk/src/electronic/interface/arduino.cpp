#include "arduino.h"
#include "serial.h"
#include <string>
#include <cstring>//for memset
#include <sstream>
#include <iostream>//debug
#include <unistd.h>
#include <stdlib.h>

using namespace std;

Arduino::Arduino()
{
	//initialise the file descriptors
	arduino[0] = 0;
	arduino[1] = 0;
	arduino[2] = 0;
}

Arduino::~Arduino()
{
	//close all open ttyUSB connections
	for(int i = 0; i < 3; i++)
	{
		if(arduino[i])
			close(arduino[i]);
	}
}

void Arduino::init()
{
	//figure out which arduino is which. 0=sensor, 1=servo, 2=motor
	int arduino_fd = 0;	//temporary one

	//various more or less temporary variables
	string usbadapter, error;
	ostringstream number;
	char buf[5];

	for(int i = 0; i < 3; i++)
	{
		//build a string that tells us which ttyUSB to connect to.
		usbadapter = "/dev/ttyUSB";
		number.str("");//clear

		number << i;
		usbadapter.append(number.str());
		//ok, the USB adapter has been built.

		arduino_fd = serialport_init(usbadapter.c_str(), 9600);	//open it up

		//check for errors
		if(arduino_fd < 0)
		{
			error = "error opening device " + usbadapter;
			perror(error.c_str());
			continue;		//don't bother doing any checks if the device doesn't exist.
		}
		else
		{
			cout << "Communication with " << usbadapter << " established!" << endl;
		}

		memset(&buf, 0, 5);	//clear our buffer before we write anything into it.

		//now, ask the arduino which one it is! send it a '?;'
		serialport_write(arduino_fd, "?;");
		//let it think... we're not in a hurry since this is initialisation business.
		usleep(50000);
		serialport_read_until(arduino_fd, (char*)&buf, ';');	//get the reply


		//sort the arduino into the right place in the array. Make sure, that only 1 servo is assigned to each task,
		// just in case somebody programmed an arduino wrongly.

		switch(buf[0])
		{
			case 's':		//sensors
				if(!arduino[0])
					arduino[0] = arduino_fd;
				else
				{
					cout << "Error! 2 arduinos claim to handle sensors!" << endl;
					return;
				}		
				break;
			case 'c':		//the control thingy, i.e. the servos... sorry, only 1 s available
				if(!arduino[1])				
					arduino[1] = arduino_fd;
				else
				{
					cout << "Error! 2 arduinos claim to control servos!" << endl;
					return;
				}
				break;
			case 'm':		//the motor
				if(!arduino[2])
					arduino[2] = arduino_fd;
				else
				{
					cout << "Error! 2 arduinos claim to control the motors!" << endl;
					return;
				}
				break;
		}//end switch

	}	//end for loop
}

//-----------------------------------------------------sensor part
void Arduino::getIRreadings(int* vals)
{
	char buf[128];
	memset(&buf, 0, 128);

	if(serialport_write(arduino[0], "i;\n") == -1)
		cout << "An error occured while requesting the IR ranges." << endl;

	usleep(50000);
	serialport_read_until(arduino[0], (char*)&buf, ';');

	istringstream iss (buf);

	memset(&vals, 0, 4);	//clear the first 4 instances of vals.

	for(int i = 0; i < 4; i++)
	{
		iss >> vals[i];
	}

}

int Arduino::getCompassreading()
{
	char buf[128];
	memset(&buf, 0, 128);

	if(serialport_write(arduino[0], "c;\n") == -1)
		cout << "An Error occured while requesting the compass reading." << endl;

	usleep(50000);
	serialport_read_until(arduino[0], (char*)&buf, ';');

	int reading = atoi((char*)&buf);
	if(reading == 0 || buf == "0")
		return -1;

	return reading;
}

//----------------------------------------end of sensor part
