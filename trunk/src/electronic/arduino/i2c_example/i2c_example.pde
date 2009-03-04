#include <SoftwareServo.h>
//#include <Servo.h> //trying software servo now
#include <Wire.h>
SoftwareServo s1;
SoftwareServo s2;
SoftwareServo s3;
int cycles = 0;
int angle;

void setup(){
 Serial.begin(9600);
 Serial.println("RESET :: Serial Debug Mode -> Enabled");
 s1.attach(8);
 s1.setMaximumPulse(2200);
 s2.attach(9);
 s2.setMaximumPulse(2200);
 s3.attach(10);
 s3.setMaximumPulse(2200);
 Wire.begin(0x0F); //address 0x0f
 Wire.onReceive(receive_event); //handler
}

void loop(){
  //do nothing..
  if(cycles++ >= 5000){
    SoftwareServo::refresh();
    cycles = 0;
  }
  //delay(10);
}

void receive_event(int bytes){
  angle = Wire.receive();
  s1.write(angle);
  s2.write(angle);
  Serial.println(angle, DEC);
}
