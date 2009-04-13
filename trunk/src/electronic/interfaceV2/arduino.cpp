#include <iostream>
#include <stdlib.h>
#include "arduino.h"

using namespace std;

using namespace LibSerial;

#define BAUDRATE SerialStreamBuf::BAUD_9600
#define IR_SENSOR_NUM 4
#define US_SENSOR_NUM 2
#define SERVO_NUM 6 //Change to 12 when servo-shield fixed

const char *arduinoNames[NUMOFARDUINOS] = // Must agree with the enum in arduino.h
{	"/dev/arduino_A7006SQw", //Sensors
	"/dev/arduino_A7006S82", //Servos
	"/dev/arduino_A9005aVz"}; //Ultrasound


arduino_t::arduino_t() //Constructor
{
	bigCompassHeading = 0;
	debugVal = 0;
}

arduino_t::~arduino_t() //Destructor
{
	for(int i = 0; i < NUMOFARDUINOS; i++) {
		ss[i].Close();
	}
}

int arduino_t::open(int arduinoNum) //Opens a single arduino
{
	if(arduinoNum < NUMOFARDUINOS) {
		ss[arduinoNum].Open(arduinoNames[arduinoNum]); //Open port
		ss[arduinoNum].SetBaudRate(SerialStreamBuf::BAUD_9600); //Set Baudrate
		ss[arduinoNum].SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
		if(ss[arduinoNum].IsOpen()) {
			cout << "Success fully openeded " << arduinoNames[arduinoNum] << endl;
			return 0; //Success!
		} else {
			cerr << "Error: couldn't open arduino " << arduinoNum << endl;
			return -1;
		}	
	} else {
		cerr << "Error: tried to open non-existant arduino " << arduinoNum << endl;
		return -1;
	}
}
int arduino_t::close(int arduinoNum) //Closes a single arduino
{
	if(arduinoNum < NUMOFARDUINOS) {
		ss[arduinoNum].Close(); //Close port
		if (!ss[arduinoNum].IsOpen()) {
			return 0; //Success!
		} else {
			cerr << "Error: Couldn't close arduino " << arduinoNum << endl;
			return -1;
		}	
	} else {
		cerr << "Error: tried to close non-existant arduino " << arduinoNum <<  endl;
		return -1;
	}
}

bool arduino_t::isOpen(int arduinoNum) 
{
	if(arduinoNum < NUMOFARDUINOS) {
		return ss[arduinoNum].IsOpen();	
	} else {
		cerr << "Error: tried to check state of non-existant arduino " << arduinoNum << endl;
		return false;
	}
}
	//----------Sensor Arduino------------------------------------------


void arduino_t::getIR(int *IRVals) //Writes readings into IRVals
{
	if(ss[SENSORS].IsOpen()) {
		ss[SENSORS] << 'i'; //Request IR readings from arduino

		for (int i = 0; i < IR_SENSOR_NUM; i++)
		{
			ss[SENSORS] >> IRVals[i]; //Read IRVals in
		}

	} else {
		cerr << "Error: Can't retrieve IR readings - Sensor arduino connection not open" << endl;
	}
}

int arduino_t::getCompass() //Returns a pointer to an int
{
	if(ss[SENSORS].IsOpen()) {
		ss[SENSORS] << 'c'; //Request compass readings from arduino
		int CompassVal = 0;
		//usleep(20000);
		ss[SENSORS] >> CompassVal; //Read CompassVal in
		//cout << "compassVal is " << CompassVal << endl;
		return CompassVal;
	} else {
		cerr << "Error: Can't retrieve compass readings - Sensor arduino connection not open" << endl;
		return -1; 
	}	
}

int arduino_t::setCompassHandler() 
{
	//threadIngredients_t threadIngredients; //Create threadIngredients
	//threadIngredients.arduino = this;
	//threadIngredients.func = &(arduino_t::getCompass());

	pthread_create(&compassHandlingThread, NULL, &(arduino_t::compassHandlingRoutine), (void *)this);
}

void *arduino_t::compassHandlingRoutine(void *arduino_t_ptr) // Static routine 
{
	
	int newHeading = 0;
	int intHeading = ((arduino_t *)arduino_t_ptr)->getCompass(); // getcompass()
	
	while(true) { //Loop forever (until thread destroyed)
		newHeading = ((arduino_t *)arduino_t_ptr)->getCompass(); // getcompass()

		if(intHeading >= 0) {
			if(abs(newHeading-(intHeading%3600)) < 1800) { //No overflow occurred		
				intHeading -= intHeading%3600; //Reduce to a whole number of revolutions
				intHeading += newHeading; 
			} else { //Overflowed 0<->3600
				if(intHeading >= 0) {
					if(newHeading > (intHeading%3600)) { // going anti-clockwise
						intHeading -= intHeading%3600; //Reduce to whole number of revs
						intHeading -= 3600; //Take off extra rev
						intHeading += newHeading;
					} else {
						intHeading -= intHeading%3600; //Reduce to whole number of revs
						intHeading += 3600; //Add on extra rev
						intHeading += newHeading; 
					}
				}  
			}
		} else { // if intHeading is negative, needs modulo correction (+3600)
			if(abs(newHeading-((intHeading%3600)+3600)) < 1800) { //No overflow occurred		
				intHeading -= (intHeading%3600)+3600; //Reduce to a whole number of revolutions
				intHeading += newHeading; 
			} else { //Overflowed 0<->3600
				if(intHeading >= 0) {
					if(newHeading > ((intHeading%3600)+3600)) { // going anti-clockwise
						intHeading -= (intHeading%3600)+3600; //Reduce to whole number of revs
						intHeading -= 3600; //Take off extra rev
						intHeading += newHeading;
					} else {
						intHeading -= (intHeading%3600)+3600; //Reduce to whole number of revs
						intHeading += 3600; //Add on extra rev
						intHeading += newHeading; 
					}
				}  
			}
		}
		((arduino_t *)arduino_t_ptr)->bigCompassHeading = intHeading;
		usleep(200000); //~10Hz refresh rate of compass heading
	}
}

int arduino_t::getBigHeading() 
{
	return bigCompassHeading;
}

int arduino_t::getSmallHeading()
{
	return (bigCompassHeading%3600);
}
	//----------UltraSound Arduino--------------------------------------
void arduino_t::getUS(int *USVals) //Returns a pointer to an array of 2 ints
{
	if(isOpen(ULTRASOUND)) {
		ss[ULTRASOUND] << 'u'; //Request ultrasound readings from arduino
		for(int i = 1; i < US_SENSOR_NUM; i++) {
			ss[ULTRASOUND] >> USVals[i]; //Read USVals in
		}
	} else {
		cerr << "Error: Can't retrieve ultrasound readings - Ultrasound arduino connection not open" << endl; 
	}	
}

	//----------Servo Arduino----------------
void arduino_t::setServoAngle(int servoNum, int angle)
{
	if(isOpen(SENSORS)) {
		if(servoNum < SERVO_NUM) {
			if(angle > 180) {
				angle = 180;
			}
			if(angle < 0) {
				angle = 0;
			}
			ss[SERVOS] << 's' << servoNum << 'm' << angle << endl;	//May need altering - not sure about how libserial sends integers (BCD or not?)
		} else {
			cerr << "Error: tried to set non-existant servo angle" << endl;
		}
	} else {
		cerr << "Error: can't set servo angle - sensor arduino connection not open" << endl;
	}
}
void arduino_t::setServoMax(int servoNum, int uSTime)
{
	if(isOpen(SENSORS)) {
		if(servoNum < SERVO_NUM) {
			ss[SERVOS] << 's' << servoNum << 'x' << uSTime << endl;	//May need altering - not sure about how libserial sends integers (BCD or not?)
		} else {
			cerr << "Error: tried to set non-existant servo max" << endl;
		}
	} else {
		cerr << "Error: can't set servo max - sensor arduino connection not open" << endl;
	}

}
void arduino_t::setServoMin(int servoNum, int uSTime)
{	
	if(isOpen(SENSORS)) {
		if(servoNum < SERVO_NUM) {
			ss[SERVOS] << 's' << servoNum << 'n' << uSTime << endl;	//May need altering - not sure about how libserial sends integers (BCD or not?)
		} else {
			cerr << "Error: tried to set non-existant servo min" << endl;
		}
	} else {
		cerr << "Error: can't set servo min - sensor arduino connection not open" << endl;
	}
}
