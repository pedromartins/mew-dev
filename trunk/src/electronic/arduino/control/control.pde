// Arduino

#include <SoftwareServo.h>

#define BAUDRATE 9600

SoftwareServo servos[12];
signed int instructionData, i;

char servoNum, stringInLength = 0;
unsigned char inByte = 0, prevInByte = 0;
boolean parsing = false;

unsigned char stringIn[5]; //Holds the command sequence

void setup()
{
	Serial.begin(BAUDRATE); //Initialise the serial
	for(i=0; i<12; i++) { 
		servos[i].attach(i+2); //Attach each servo
	}
}

void loop()
{
	while (Serial.available() > 0) {
		prevInByte = inByte;
		inByte =  Serial.read();

		if(parsing) {
			stringIn[stringInLength] = inByte; //Store into a string
			stringInLength++;

			if(stringInLength >= 4) { //Whole command data has been stored
				servoNum = stringIn[0];

				instructionData = 256*stringIn[2] + stringIn[3]; //Extract instruction data

				switch(stringIn[1]) { 	//Execute command
					case 'm': //Move servo
                                                servos[servoNum].write(instructionData);
						break;
					case 'n': //Set min of servo
						servos[servoNum].setMinimumPulse(instructionData);
						break;
					case 'x': //Set max of servo
						servos[servoNum].setMaximumPulse(instructionData);
						break;		
					default: break;			
				}		
				stringInLength = 0; //Reset parsing control variables
				parsing = false;		
			}
		}

		if(!parsing) {

			if ((prevInByte == 's') && (inByte == 'c')) { //We have found the start command
					parsing = true;
				        stringInLength = 0;
			}

			if ((prevInByte == '?') && (inByte == ';')) { //Arduino function requested
					Serial.print("c;");
			}

		}
	} 
	SoftwareServo::refresh();
}

