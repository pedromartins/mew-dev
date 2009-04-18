#include <SerialStream.h>	//requires apt-get install libserial0 libserial-dev
#include <pthread.h>

using namespace LibSerial;

enum {SENSORS, SERVOS, MOTORS, NUMOFARDUINOS};

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
		int compassHeadingRefreshRate; //Rate (in Hz) of handlingThreads queries
		pthread_t compassHandlingThread;
		pthread_mutex_t sensorMutex; // Stops simultaneous requesting of compass and IR values
		bool threadRunning; //Flag
		static void *compassHandlingRoutine(void *threadIngredients);

		int getCompass(); //Returns compass heading

		int setCompassHandler(); //Sets the compassHandlingThread going

	public:
		void getIR(int *IRVals); //Stores the current values returned from the IR sensors in *IRVals
		void getIRscan(int *IRleft, int* IRright, int* IRfrontscan, int* IRbackscan); //Scans the area around the robot
		int getBigHeading(); //Returns bigCompassHeading
		int getSmallHeading(); //Returns bigCompassHeading%3600

	/*//----------UltraSound Arduino-----------
	private: //Nothing
	public:
		void getUS(int *USVals); //Stores values using passed pointer USVals
	*/
	//----------Servo Arduino----------------
	private: //Nothing
	public:
		void setServoAngle(int servoNum, int angle);
		void setServoMax(int servoNum, int uSTime);
		void setServoMin(int servoNum, int uSTime);
	
	//----------Motor Arduino----------------
	#define MOTOR_NUM 2
	#define MOTOR_BACKWARDS 0
	#define MOTOR_FORWARD 1
	private: //Nothing
	public:
		void setMotorPWM(int motorNum, int dutyCycle);
		void setMotorDir(int motorNum, int direction);
};

