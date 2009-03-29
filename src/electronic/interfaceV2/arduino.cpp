#include <iostream>
#include "arduino.h"

using namespace std;

using namespace LibSerial;

const char *arduinoNames[NUMOFARDUINOS] = // Must agree with the enum in arduino.h
{	"/dev/arduino_A7006SQw", //Sensors
	"/dev/arduino_A7006S82", //Servos
	"/dev/arduino_A9005aVz"}; //Ultrasound


Arduinos::Arduinos() //Constructor
{
	for(int i = 0; i < NUMOFARDUINOS; i++) { //Initialise status to inactive
		arduino[i].active = false;
	}	
}

Arduinos::~Arduinos() //Destructor
{
	for(int i = 0; i < NUMOFARDUINOS; i++) {
		arduino[i].ss.Close();
		arduino[i].active = false;
	}
}

int Arduinos::open(int arduinoNum) //Opens a single arduino
{
	if(arduinoNum >= NUMOFARDUINOS) {
		cerr << "Error: tried to open non-existant arduino" << endl;
		return -1;
	} else {
		if (arduino[arduinoNum].active) {
			cerr << "Error: tried to open port which is already opened" << endl;
			return -1;
		} else {
			arduino[arduinoNum].ss.Open(arduinoNames[arduinoNum]); //Open port
			arduino[arduinoNum].ss.SetBaudRate(SerialStreamBuf::BAUD_9600); //Set Baudrate
			arduino[arduinoNum].ss.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
			arduino[arduinoNum].active = true; //Set active flag
		}
	}
	return 0;
}
int Arduinos::close(int arduinoNum) //Closes a single arduino
{
	if(arduinoNum >= NUMOFARDUINOS) {
		cerr << "Error: tried to close non-existant arduino" << endl;
		return -1;
	} else {
		if (arduino[arduinoNum].active) {
			cerr << "Error: tried to close port which is already closed" << endl;
			return -1;
		} else {
			arduino[arduinoNum].ss.Close(); //Close port
			arduino[arduinoNum].active = true; // Reset active flag
		}
	}
	return 0;
}
	
	//----------Sensor Arduino---------------
void Arduinos::getIR(int *IRVals) 
{
	if(!arduino[SENSORS].active) {
		cerr << "Error: Can't retrieve IR readings - Sensor arduino not active" << endl;
		return; 
	}

	arduino[SENSORS].ss << 'i'; //Request IR readings from arduino

	for (int i = 0; i < 4; i++) {
			arduino[SENSORS].ss >> IRVals[i];
	}
}
int Arduinos::getCompass() //Returns a pointer to an int
{
	if(!arduino[SENSORS].active) {
		cerr << "Error: Can't retrieve compass readings - Sensor arduino not active" << endl;
		return -1; 
	}
	arduino[SENSORS].ss << 'c'; //Request compass readings from arduino

	int CompassVal = 0;
	arduino[SENSORS].ss >> CompassVal;

	return CompassVal;

}

	//----------UltraSound Arduino-----------
void Arduinos::getUS(int *USVals) //Returns a pointer to an array of 2 ints
{
	return;
}

	//----------Servo Arduino----------------
int Arduinos::setServoAngle(int servoNum, int angle)
{
	return 0;
}
int Arduinos::setServoMax(int servoNum, int uSTime)
{
	return 0;
}
int Arduinos::setServoMin(int servoNum, int uSTime)
{
	return 0;
}
