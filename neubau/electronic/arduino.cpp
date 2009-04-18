#include <iostream>
#include <stdlib.h>
#include <electronic/arduino.h>

using namespace std;

using namespace LibSerial;

#define BAUDRATE SerialStreamBuf::BAUD_9600
#define IR_SENSOR_NUM 4
#define SERVO_NUM 12

// TODO Get rid of these hardcoded serial numbers and have the arduinos identify themselves again
const char *arduinoNames[NUMOFARDUINOS] = // Must agree with the enum in arduino.h
{	"/dev/arduino_A7006SQw", //Sensors
	"/dev/arduino_A7006S82", //Servos
	"/dev/arduino_A9005aVz"}; //Motors


ArduinoManager::ArduinoManager()
{
	bigCompassHeading = 0;
	compassHeadingRefreshRate = 220; // 10Hz default refresh rate
	threadRunning = false; // Initialise thread running flag

	// Mutex used to stop simultaneous requests for sensor readings
	pthread_mutex_init(&sensorMutex, NULL);
}

ArduinoManager::~ArduinoManager()
{
	for(int i = 0; i < NUMOFARDUINOS; i++) {
		ss[i].Close();
	}
}

bool ArduinoManager::open(int arduinoNum) //Opens a single arduino
{
	if(arduinoNum < NUMOFARDUINOS) {
		ss[arduinoNum].Open(arduinoNames[arduinoNum]); //Open port
		ss[arduinoNum].SetBaudRate(SerialStreamBuf::BAUD_57600); //Set Baudrate
		ss[arduinoNum].SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
		if(ss[arduinoNum].IsOpen()) {
			return true;
		} else {
			cerr << "Error: couldn't open arduino " << arduinoNum << endl;
			return false;
		}
	} else {
		cerr << "Error: tried to open non-existant arduino " << arduinoNum << endl;
		return false;
	}
}

bool ArduinoManager::close(int arduinoNum) //Closes a single arduino
{
	if(arduinoNum < NUMOFARDUINOS) {
		ss[arduinoNum].Close(); //Close port
		if (!ss[arduinoNum].IsOpen()) {
			return true;
		} else {
			cerr << "Error: Couldn't close arduino " << arduinoNum << endl;
			return false;
		}
	} else {
		cerr << "Error: tried to close non-existant arduino " << arduinoNum <<  endl;
		return false;
	}
}

bool ArduinoManager::isOpen(int arduinoNum)
{
	if(arduinoNum < NUMOFARDUINOS) {
		return ss[arduinoNum].IsOpen();
	} else {
		cerr << "Error: tried to check state of non-existant arduino " << arduinoNum << endl;
		return false;
	}
}
	//----------Sensor Arduino------------------------------------------


void ArduinoManager::getIR(int *IRVals) //Writes readings into IRVals
{
	if(ss[SENSORS].IsOpen()) {
		pthread_mutex_lock (&sensorMutex); //Lock the sensor arduino
		ss[SENSORS] << 'i'; //Request IR readings from arduino
		for (int i = 0; i < IR_SENSOR_NUM; i++)
		{	
			ss[SENSORS] >> IRVals[i]; //Read IRVals in
		}
		pthread_mutex_unlock(&sensorMutex); // Release the sensor arduino

	} else {
		cerr << "Error: Can't retrieve IR readings - Sensor arduino connection not open" << endl;
	}
}

int ArduinoManager::getCompass() //Returns a pointer to an int
{
	if(ss[SENSORS].IsOpen()) {
		pthread_mutex_lock (&sensorMutex); //Lock the sensor arduino
		ss[SENSORS] << 'c'; //Request compass readings from arduino
		int CompassVal = 0;
		ss[SENSORS] >> CompassVal; //Read CompassVal in
		pthread_mutex_unlock (&sensorMutex); //Release the sensor arduino
		return CompassVal;
	} else {
		cerr << "Error: Can't retrieve compass readings - Sensor arduino connection not open" << endl;
		return -1; 
	}	
}

int ArduinoManager::setCompassHandler()
{	// Creates a thread which handles the compass (including angle overflows)
	if(!threadRunning) {
		pthread_create(&compassHandlingThread, NULL, &(ArduinoManager::compassHandlingRoutine), (void *)this);
	threadRunning = true;
	}
}

void *ArduinoManager::compassHandlingRoutine(void *arduino_t_ptr) // Static routine
{

	int newHeading = 0;
	int intHeading = ((ArduinoManager *)arduino_t_ptr)->getCompass(); // getcompass()

	while(true) { //Loop forever (until thread destroyed)
		newHeading = ((ArduinoManager *)arduino_t_ptr)->getCompass(); // getcompass()

		if(intHeading >= 0) {
			if(abs(newHeading-(intHeading%3600)) < 1800) { //No overflow occurred
				intHeading -= intHeading%3600; //Reduce to a whole number of revolutions
				intHeading += newHeading;
			} else { //Overflowed 0<->3600
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
		} else { // if intHeading is negative, needs modulo correction (+3600)
			if(abs(newHeading-((intHeading%3600)+3600)) < 1800) { //No overflow occurred
				intHeading -= (intHeading%3600)+3600; //Reduce to a whole number of revolutions
				intHeading += newHeading;
			} else { //Overflowed 0<->3600
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
		((ArduinoManager *)arduino_t_ptr)->bigCompassHeading = intHeading;
		usleep(1000000/((ArduinoManager *)arduino_t_ptr)->compassHeadingRefreshRate); //Delay
	}
}

int ArduinoManager::getBigHeading()
{
	if(!threadRunning) { //Run the thread
		setCompassHandler();
		usleep(100000); // Allow the thread to get some values
	}
	return bigCompassHeading;
}

int ArduinoManager::getSmallHeading()
{
	if(!threadRunning) { //Run the thread
		setCompassHandler();
		usleep(100000); // Allow the thread to get some values
	}
	return (bigCompassHeading%3600);
}
	//----------UltraSound Arduino--------------------------------------
/*void ArduinoManager::getUS(int *USVals) //Returns a pointer to an array of 2 ints
{
	if(isOpen(ULTRASOUND)) {
		ss[ULTRASOUND] << 'u'; //Request ultrasound readings from arduino
		for(int i = 1; i < US_SENSOR_NUM; i++) {
			ss[ULTRASOUND] >> USVals[i]; //Read USVals in
		}
	} else {
		cerr << "Error: Can't retrieve ultrasound readings - Ultrasound arduino connection not open" << endl;
	}
}*/

	//----------Servo Arduino----------------
void ArduinoManager::setServoAngle(int servoNum, int angle)
{
	if(isOpen(SENSORS)) {
		if(servoNum < SERVO_NUM) {
			if(angle > 180) {
				angle = 180;
			}
			if(angle < 0) {
				angle = 0;
			}
			ss[SERVOS] << 's' << servoNum << 'm' << angle << endl;
		} else {
			cerr << "Error: tried to set non-existant servo angle" << endl;
		}
	} else {
		cerr << "Error: can't set servo angle - sensor arduino connection not open" << endl;
	}
}
void ArduinoManager::setServoMax(int servoNum, int uSTime)
{
	if(isOpen(SENSORS)) {
		if(servoNum < SERVO_NUM) {
			ss[SERVOS] << 's' << servoNum << 'x' << uSTime << endl;
		} else {
			cerr << "Error: tried to set non-existant servo max" << endl;
		}
	} else {
		cerr << "Error: can't set servo max - sensor arduino connection not open" << endl;
	}

}
void ArduinoManager::setServoMin(int servoNum, int uSTime)
{
	if(isOpen(SENSORS)) {
		if(servoNum < SERVO_NUM) {
			ss[SERVOS] << 's' << servoNum << 'n' << uSTime << endl;
		} else {
			cerr << "Error: tried to set non-existant servo min" << endl;
		}
	} else {
		cerr << "Error: can't set servo min - sensor arduino connection not open" << endl;
	}
}

	//---------Motor Arduino-----------------

void ArduinoManager::setMotorPWM(int motorNum, int dutyCycle) 
{
	if(isOpen(MOTORS)) {
		if(motorNum < MOTOR_NUM) {
			if(dutyCycle > 255) {
				dutyCycle = 255;
			}
			if(dutyCycle < 0) {
				dutyCycle = 0;
			}
			ss[MOTORS] << 'm' << motorNum << 'p' << dutyCycle << ';' << endl;	
		} else {
			cerr << "Error: tried to set PWM for non-existant motor" << endl;
		}
	} else {
		cerr << "Error: can't set motor PWM - motor arduino connection not open" << endl;
	}
}
	
void ArduinoManager::setMotorDir(int motorNum, int direction)
{
	if(isOpen(MOTORS)) {
		if(motorNum < MOTOR_NUM) {
			if(direction != 0) {
				direction = 1;
			}

			ss[MOTORS] << 'm' << motorNum << 'd' << direction << ';' << endl;	
		} else {
			cerr << "Error: tried to set direction for non-existant motor" << endl;
		}
	} else {
		cerr << "Error: can't set motor direction - motor arduino connection not open" << endl;
	}
}
