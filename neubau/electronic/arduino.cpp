#include "arduino.h"
#include "serial.h"
#include <string>
#include <cstring>//for memset
#include <sstream>
#include <iostream>//debug
#include <unistd.h>
#include <stdlib.h>

using namespace std;

const char *arduinoNames[NUMOFARDUINOS] = // Must agree with the enum in arduino.h
{	"/dev/arduino_A7006SQw", //Sensors
	"/dev/arduino_A7006S82", //Control
	"/dev/arduino_A9005aVz"}; //Ultrasound

Arduino::Arduino()
{
	//initialise the file descriptors
	for(int i=0; i<NUMOFARDUINOS; i++) {
		arduino[i] = 0;
	}
}

Arduino::~Arduino()
{
	//close all open ttyUSB connections
	for(int i = 0; i < NUMOFARDUINOS; i++)
	{
		if(arduino[i])
			serialport_close(arduino[i]);
	}
}

void Arduino::init()
{
	//figure out which arduino is which. 0=sensor, 1=servo, 2=motor
	int arduino_fd = 0;	//temporary one

	//various more or less temporary variables
	string usbadapter, error;
	ostringstream number;
	char buf[128];


	for(int i = 0; i < NUMOFARDUINOS; i++)
	{
		//Fetch adapter name
		usbadapter = arduinoNames[i];
		
		usleep(500000);

		arduino_fd = serialport_init(usbadapter.c_str(), BAUDRATE);	//open it up
		serialport_close(arduino_fd);
		arduino_fd = serialport_init(usbadapter.c_str(), BAUDRATE);	//open it up

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
		
		arduino[i] = arduino_fd;
		serialport_read_until(arduino[i], buf, '!');
	}
		/*memset(&buf, 0, 5);	//clear our buffer before we write anything into it.

		 usleep(500000);
		//now, ask the arduino which one it is! send it a '?;'
		serialport_write(arduino_fd, "?;");
		//let it think... we're not in a hurry since this is initialisation business.
		usleep(500000);
		serialport_read_until(arduino_fd, (char*)&buf, ';');	//get the reply
		usleep(500000);

		//sort the arduino into the right place in the array. Make sure, that only 1 servo is assigned to each task,
		// just in case somebody programmed an arduino wrongly.

		switch(buf[0])
		{
			case 's':		//sensors
				if(!arduino[SENSORS])
					arduino[SENSORS] = arduino_fd;
				else
				{
					cout << "Error! 2 arduinos claim to handle sensors!" << endl;
					return;
				}		
				break;
			case 'c':		//the control thingy, i.e. the servos... sorry, only 1 s available
				if(!arduino[CONTROL])				
					arduino[CONTROL] = arduino_fd;
				else
				{
					cout << "Error! 2 arduinos claim to control servos!" << endl;
					return;
				}
				break;
			case 'u':		//the ultrasound arduino
				if(!arduino[ULTRASOUND])
					arduino[ULTRASOUND] = arduino_fd;
				else
				{
					cout << "Error! 2 arduinos claim to read the ultrasound sensors!" << endl;
					return;
				}
				break;
		}//end switch

	}	//end for loop

	//tell us which arduino is where
	*/
}

//check connection
bool Arduino::checkConnection(int a)
{
	if(arduino[a] <= 0)	//check it's filedescriptor
	{
		cout << "Error trying to connect to  " << arduinoNames[a] << "! Aborting function call." << endl;
		return false;
	}
	return true;
}

//-----------------------------------------------------sensor part
void Arduino::getIRreadings(int* vals)
{
	if(!checkConnection(SENSORS))
		return;

	char buf[128];
	memset(&buf, 0, 128);

	if(serialport_writebyte(arduino[SENSORS], 'i') == -1)
		cout << "An error occured while requesting the IR ranges." << endl;

	usleep(50000);
	stringstream ss; 
	memset(vals, 0, 4);	//clear the first 4 instances of vals.

	//cout << "Arduino printed " << buf << endl;


	for(int i = 0; i < 4; i++)
	{
		serialport_read_until(arduino[SENSORS], buf, '\n');
		cout << "Buffer is " << buf << endl;
		ss << buf;
		ss >> vals[i];
	}

}

int Arduino::getCompassreading()
{
	if(!checkConnection(SENSORS))
		return -1;

	char buf[128];
	memset(buf, 0, 128);

	if(serialport_writebyte(arduino[SENSORS], 'c') == -1)
		cout << "An Error occured while requesting the compass reading." << endl;

	usleep(50000);
	serialport_read_until(arduino[SENSORS], buf, '\n');

	int reading = atoi(buf);
	/*if(reading == 0 || buf == "0")
		return -1;*/

	return reading;
}

void Arduino::getUSreadings(int* vals)
{
	if(!checkConnection(ULTRASOUND))
		return;
	cout << "in getUS" << endl;
	char buf[128];
	memset(buf, 0, 128);

	usleep(50000);
	if(serialport_writebyte(arduino[ULTRASOUND], 'u') == -1)
		cout << "An error occured while requesting the IR ranges." << endl;

	usleep(50000);

	stringstream ss;
	cout << "after ss" << endl;
	for(int i = 0; i < 2; i++)
	{
		cout << "in loop " << i << endl;
		serialport_read_until(arduino[ULTRASOUND], buf, '\n');
		cout << "Buffer is " << buf << endl;
		ss << buf;
		ss >> vals[i];
	}

}

//----------------------------------------end of sensor part

//-----------------------------------------------------control part

void Arduino::dropLintel() {
	if(!checkConnection(CONTROL))
		return;

	servos_setPos(LINTELSERVO, 15);
}

void Arduino::resetLintel() {
	if(!checkConnection(CONTROL))
		return;

	servos_setPos(LINTELSERVO, 50);
}

void Arduino::servos_setPos(char servoNum, int inAngle)
{
	//Moves a servo to specified angle.
	int angle = inAngle;

	if(angle > 180) angle = 180; //Constrain angle to within servo limits
	if(angle < 0) angle = 0;
	
	//Write command string to the serial port
	serialport_writebyte(arduino[CONTROL],'s');
	serialport_writebyte(arduino[CONTROL],'c');
	serialport_writeubyte(arduino[CONTROL],servoNum);
	serialport_writebyte(arduino[CONTROL],'m');
	serialport_writeubyte(arduino[CONTROL],0);
	serialport_writeubyte(arduino[CONTROL],angle);
//	serialport_writebyte(arduino[CONTROL],';');
}

void Arduino::servos_setMin(int servoNum, int inNum)
{
	//Changes a servos minimum pulse length (in uSeconds)
	
	int LSByte, MSByte;

	LSByte = inNum%256;
	MSByte = (inNum-LSByte)/256;

	//Write command string to the serial port
	serialport_writebyte(arduino[CONTROL],'s');
	serialport_writebyte(arduino[CONTROL],'c');
	serialport_writeubyte(arduino[CONTROL],servoNum);
	serialport_writebyte(arduino[CONTROL],'n');
	serialport_writeubyte(arduino[CONTROL],MSByte);
	serialport_writeubyte(arduino[CONTROL],LSByte);
//	serialport_writebyte(arduino[CONTROL],';');
}

void Arduino::servos_setMax(int servoNum, int inNum)
{
	//Changes a servos maximum pulse length (in uSeconds)
	
	int LSByte, MSByte;

	LSByte = inNum%256;
	MSByte = (inNum-LSByte)/256;

	//Write command string to the serial port
	serialport_writebyte(arduino[CONTROL],'s');
	serialport_writebyte(arduino[CONTROL],'c');
	serialport_writeubyte(arduino[CONTROL],servoNum);
	serialport_writebyte(arduino[CONTROL],'x');
	serialport_writeubyte(arduino[CONTROL],MSByte);
	serialport_writeubyte(arduino[CONTROL],LSByte);
//	serialport_writebyte(arduino[CONTROL],';');
}

//-----------------------------------------------------end of control part
