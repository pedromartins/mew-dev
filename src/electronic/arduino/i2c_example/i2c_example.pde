//#include <SoftwareServo.h>
//#include <Servo.h> //trying software servo now
#include <Wire.h>
int cycles = 0;
int angle;

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


void setup(){
 Serial.begin(9600);
 pinMode(IR_pin,INPUT);
 Serial.println("RESET :: Serial Debug Mode -> Enabled");
 Wire.begin(0x0f); //address 0x0f
 Wire.onReceive(receive_event); //handler
 Wire.onRequest(request_event); //handler
}

void loop(){
  //do nothing..
  if(cycles++ >= 5000){
  //  SoftwareServo::refresh();
    cycles = 0;
  }
  //delay(10);
}

void request_event()
{
  byte b = 12;
    Wire.send(b);
  Serial.println(1, DEC);
}

void receive_event(int bytes){
  distance = read_gp2d12_range(IR_pin);
  byte b = 12;
  angle = Wire.receive();
  Wire.send(b);
  Serial.println(angle, DEC);
  Serial.println(distance, DEC);
}
