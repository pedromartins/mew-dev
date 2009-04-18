#include <SerialStream.h>	//requires apt-get install libserial0 libserial-dev
#include <pthread.h>

using namespace LibSerial;

enum {SENSORS, SERVOS, ULTRASOUND, NUMOFARDUINOS};

/**
 * ArduinoManager manages the use and lifecycle of several pre-defined Arduino devices.
 *
 * Should limit to singleton instance asap.
 */
class ArduinoManager {
	private:
		SerialStream ss[NUMOFARDUINOS];
	public:
		ArduinoManager();
		~ArduinoManager();
		bool open(int arduinoNum); //Opens a single arduino
		bool close(int arduinoNum); //Closes a single arduino
		bool isOpen(int arduinoNum); //Returns true if specified arduino is active.
	//----------Sensor Arduino---------------
	private:
		int bigCompassHeading; // Holds multi-turn compass heading
		pthread_t compassHandlingThread;
		static void *compassHandlingRoutine(void *threadIngredients);

		void getIR(int *IRVals); //Stores the current values returned from the IR sensors in *IRVals
		int getCompass(); //Returns compass heading

		int setCompassHandler(); //Sets the compassHandlingThread going

	public:
		void getIRscan(int *IRleft, int* IRright, int* IRfrontscan, int* IRbackscan); //Scans the area around the robot
		int getBigHeading(); //Returns bigCompassHeading
		int getSmallHeading(); //Returns bigCompassHeading%3600

	//----------UltraSound Arduino-----------
	private: //Nothing
	public:
		void getUS(int *USVals); //Stores values using passed pointer USVals

	//----------Servo Arduino----------------
	private: //Nothing
	public:
		void setServoAngle(int servoNum, int angle);
		void setServoMax(int servoNum, int uSTime);
		void setServoMin(int servoNum, int uSTime);
};

