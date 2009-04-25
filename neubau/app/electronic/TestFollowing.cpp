#include <electronic/arduino.h>
#include <unistd.h>
#include <iostream>

#define SERVOSPEED 0.0033 // Seconds per degree

using namespace std;

void scanIR(ArduinoManager&, int, int, int *);

int main (int argc, char **argv) 
{
	ArduinoManager arduinos;
	int IRVals[19];
	arduinos.open(SENSORS);
	arduinos.open(SERVOS);
	
	scanIR(arduinos, 0, 0, IRVals);

	for(int i=0; i<19; i++) 
	{
		for(int j=0; j<50; j++) 
		{
			if (IRVals[i]--)
				cout << '#';
			else 
				break;
		}
		cout << endl;
	}

	return 0;
	
}

void scanIR (ArduinoManager& arduinos, int IRNum, int servoNum, int *IRVals) 
{
	int tempIRVals[3][4];
	arduinos.setServoAngle(servoNum, 0);
	usleep(180*SERVOSPEED*1000000);
	for(int i=0, j=0; i<181; i+=10, j++) 
	{
		arduinos.setServoAngle(servoNum, i);
		usleep(10*SERVOSPEED*1000000);
		arduinos.getIR(tempIRVals[0]);
		arduinos.getIR(tempIRVals[1]);
		arduinos.getIR(tempIRVals[2]);
		IRVals[j] = (tempIRVals[0][IRNum] + tempIRVals[1][IRNum] + tempIRVals[2][IRNum])/3;
	}
}
