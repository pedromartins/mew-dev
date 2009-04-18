// Arduino

#include <SoftwareServo.h>

#define BAUDRATE 57600

SoftwareServo servos[12];
int i;

char inByte, commandByte;
int servoNumIn, commandNumIn, parseMode;

void setup()
{
	Serial.begin(BAUDRATE); //Initialise the serial
	for(i=0; i<12; i++) { 
		servos[i].attach(i+2); //Attach each servo
	}
	int parseMode = 0;
}

void loop()
{
	while (Serial.available() > 0) {
		inByte =  Serial.read();
		switch (parseMode) {
			case 0: 
				if(inByte == 's') {
					servoNumIn = 0;
					parseMode = 1; // Look for servoNumber
				}
				break;
			case 1:
				if((inByte >= '0') && (inByte <= '9')) {
					servoNumIn = servoNumIn*10 + inByte - '0';
				} else if ((inByte == 'm') || (inByte == 'x') || (inByte == 'n')) {	//Move, max, min commands
					commandByte = inByte; //Save command
					commandNumIn = 0;
					parseMode = 2; //Look for command data
				} else {
					parseMode = 0; //Invalid input, so reset
				}
				break;
			case 2:	
				if((inByte >= '0') && (inByte <= '9')) {
					commandNumIn = commandNumIn*10 + inByte - '0';
				} else if (inByte == ';') {	//End of command
					switch (commandByte) {
						case 'm': // Move servo
							servos[servoNumIn].write(commandNumIn);
							break;
						case 'x': // Set servo pulse max
							servos[servoNumIn].setMaximumPulse(commandNumIn);
							break;
						case 'n': // Set servo pulse min
							servos[servoNumIn].setMinimumPulse(commandNumIn);
							break;
					}
				} else {
					parseMode = 0; //Invalid input, so reset
				}
				break;


		}
		                
	} 
	SoftwareServo::refresh();
}

