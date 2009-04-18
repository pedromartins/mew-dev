// Arduino

#define BAUDRATE 57600
typedef struct {
	int PWM, Dir, Brake;
} motor_t;

motor_t motor[2];

int i;

char inByte, commandByte;
int motorNumIn, commandNumIn, parseMode;

void setup()
{
	// Assign pin numbers to motors
	motor[0].PWM = 5;
	motor[0].Dir = 6;
	motor[0].Brake = 7;	
	
	motor[1].PWM = 10;
	motor[1].Dir = 11;
	motor[1].Brake = 12;	

	for(i=0; i<2; i++) { // Configure the pins
		pinMode(motor[i].PWM, OUTPUT);
		analogWrite(motor[i].PWM, 0);
	
		pinMode(motor[i].Dir, OUTPUT);
		digitalWrite(motor[i].Dir, LOW);

		pinMode(motor[i].Brake, OUTPUT);
		digitalWrite(motor[i].Brake, LOW);
	}

	Serial.begin(BAUDRATE); //Initialise the serial
	int parseMode = 0;
	Serial.flush();
}

void loop()
{
	while (Serial.available() > 0) {
		inByte =  Serial.read();
		switch (parseMode) {
			case 0: 
				if(inByte == 'm') {
					motorNumIn = 0;
					parseMode = 1; // Look for servoNumber
				}
				break;
			case 1:
				if((inByte >= '0') && (inByte <= '9')) {
					motorNumIn = motorNumIn*10 + inByte - '0';
				} else if ((inByte == 'p') || (inByte == 'd') || (inByte == 'b')) {	//PWM, Dir and Brake commands
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
						case 'p': // Set PWM
							analogWrite(motor[motorNumIn].PWM, commandNumIn);
							parseMode = 0;
							break;
						case 'd': // Set direction
							if (commandNumIn == 0) {
								digitalWrite(motor[motorNumIn].Dir, LOW);
							} else {
								digitalWrite(motor[motorNumIn].Dir, HIGH);
							}
							parseMode = 0;
							break;
						case 'n': // Set Brake
							if (commandNumIn == 0) {
								digitalWrite(motor[motorNumIn].Brake, LOW);
							} else {
								digitalWrite(motor[motorNumIn].Brake, HIGH);
							}
							parseMode = 0;
							break;
					}
				} else {
					parseMode = 0; //Invalid input, so reset
				}
				break;
		}
	} 
}

