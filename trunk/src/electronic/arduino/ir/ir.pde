 int IR_pin = 0;//IR Analog pin 0
 unsigned long distance = 0;

/* 
  code from http://www.arduino.cc/playground/Main/ReadGp2d12Range
  read_gp2d12_range
  Function that reads a value from GP2D12 infrared distance sensor and returns a value in centimeters.
  
  This sensor should be used with a refresh rate of 36ms or greater.

  Javier Valencia 2008

  float read_gp2d12_range(byte pin)

  It can return -1 if something gone wrong.
 */

//outputs the IR range in cm
float read_gp2d12_range(byte pin) {
	int tmp;

	tmp = analogRead(pin);
	if (tmp < 3)
		return -1; // invalid value

	return (6787.0 /((float)tmp - 3.0)) - 4.0;
} 


void setup()
  {
  Serial.begin(9600);
  pinMode(IR_pin,INPUT);
}

void loop()
{
  distance = read_gp2d12_range(IR_pin);
  Serial.println(distance, DEC);
  delay(250); //delay 1/4 seconds.
}
