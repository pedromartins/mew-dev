#include "servos.h"
#include "serial.h"
#include <iostream>
#include <sstream>

using namespace std;

void servos_dropLintel(int port, int servoNum) {
	servos_setPos(port, servoNum, 15);
}

void servos_resetLintel(int port, int servoNum) {
	servos_setPos(port, servoNum, 50);
}

int servos_init(char serialPort[]) 
{
	//Initialises the servo library
	return serialport_init(serialPort, 38400);
}

void servos_close(int port) 
{
	close(port);
}

int servos_setPos(int port, char servoNum, int inAngle)
{
	//Moves a servo to specified angle.
	int angle;
	stringstream ss;
	string commandStr;
	
	angle = inAngle;
	if(angle > 180) angle = 180;
	if(angle < 0) angle = 0;
	
	serialport_writebyte(port,'s');
	serialport_writebyte(port,'c');
	serialport_writeubyte(port,servoNum);
	serialport_writebyte(port,'m');
	serialport_writebyte(port,0);
	serialport_writeubyte(port,angle);
	return 0;
}

int servos_setMin(int port, int servoNum, int inNum)
{
	//Changes a servos minimum pulse length (in uSeconds)
	stringstream ss;
	string commandStr;
	
	ss << "s " << servos_intToStr(servoNum, 2) << " n " << servos_intToStr(inNum, 4) << ";";
	
	commandStr = ss.str();

	//Write commandStr to the serial port
	serialport_write(port, commandStr.c_str());
	return 0;
}

int servos_setMax(int port, int servoNum, int inNum)
{
	//Changes a servos maximum pulse length (in uSeconds)
	stringstream ss;
	string commandStr;
	
	ss << "s " << servos_intToStr(servoNum, 2) << " x " << servos_intToStr(inNum, 4) << ";";
	
	commandStr = ss.str();

	//Write commandStr to the serial port
	serialport_write(port, commandStr.c_str());
	return 0;
}

char *servos_intToStr(int inNum, int numChars) 
{
	int i, num;
	char *outString = new char[numChars+1];

	num = inNum;

	for(i=1;i<=numChars;i++) {
		outString[numChars-i] = num%10+ '0';
		num = num/10;
	}
	outString[numChars] = '\0';
	
	return outString;
}
