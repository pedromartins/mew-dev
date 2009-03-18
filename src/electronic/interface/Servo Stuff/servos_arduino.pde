#include <SoftwareServo.h>

SoftwareServo servos[12];
int incomingByte, servoNum, commandNum, i, stringInLength = 0;
boolean parsing = false;

char stringIn[13];

void setup()
{
	Serial.begin(9600);
	for(i=0; i<12; i++) {
		servos[i].attach(i+2); 
		servos[i].write(90); // Attach each servo and initialise to 90 degrees.
	}
}

void loop()
{
	if (Serial.available() > 0) {
		incomingByte =  Serial.read();
		if (incomingByte == 's') {
			parsing = true;
			Serial.println("Parsing");
		}
		if(parsing) {
			stringIn[stringInLength] = incomingByte;
			stringInLength++;
			if(stringInLength >= 12) {
				stringIn[12] = '\0';
				Serial.println("finished parsing");
				servoNum = 0;
				for(i=2;i<=3;i++)	//Extract servo number
					servoNum = servoNum*10 + stringIn[i] - '0';

				commandNum = 0;
				for(i=7;i<=10;i++)	//Extract command number
					commandNum = commandNum*10 + stringIn[i] - '0';

				switch(stringIn[5]) { 	//Execute command
					case 'p':
						Serial.println("Changing position");
						servos[servoNum].write(commandNum);
						break;
					case 'n':
						servos[servoNum].setMinimumPulse(commandNum);
						break;
					case 'x':
						servos[servoNum].setMaximumPulse(commandNum);
						break;		
					default: 
						Serial.println("In default");
						Serial.println(stringIn);				
				}		
				stringInLength = 0;
				parsing = false;		
			}
		}
		
	} 
	SoftwareServo::refresh();
}

