#include <SerialStream.h>

using namespace LibSerial;

enum {SENSORS, SERVOS, ULTRASOUND, NUMOFARDUINOS};

class Arduinos {
	private:
		struct {
			SerialStream ss;
			bool active; //Actice flag
		} arduino[3];

	public:
		Arduinos();
		~Arduinos();
		int open(int arduinoNum); //Opens a single arduino
		int close(int arduinoNum); //Closes a single arduino
	
	//----------Sensor Arduino---------------
		void getIR(int *IRVals); //Returns a pointer to an array of 4 ints
		int getCompass(); //Returns a pointer to an int

	//----------UltraSound Arduino-----------
		void getUS(int *USVals); //Returns a pointer to an array of 2 ints

	//----------Servo Arduino----------------
		int setServoAngle(int servoNum, int angle);
		int setServoMax(int servoNum, int uSTime);
		int setServoMin(int servoNum, int uSTime);
};

