#include <SerialStream.h>	//requires apt-get install libserial0 libserial-dev
#include <pthread.h>

using namespace LibSerial;

enum {SENSORS, SERVOS, ULTRASOUND, NUMOFARDUINOS};

class arduino_t {
	private:
		SerialStream ss[NUMOFARDUINOS];
	public:
		arduino_t();
		~arduino_t();
		int open(int arduinoNum); //Opens a single arduino
		int close(int arduinoNum); //Closes a single arduino
		bool isOpen(int arduinoNum); //Returns true if specified arduino is active.
		int debugVal;	
	//----------Sensor Arduino---------------
	private:
		int bigCompassHeading; // Holds multi-turn compass heading
		pthread_t compassHandlingThread; 
		static void *compassHandlingRoutine(void *threadIngredients);
	public:	
		void getIR(int *IRVals); //Stores values in IRVals
		int getCompass(); //Returns compass heading
		int setCompassHandler(); //Sets the compassHandlingThread going
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

