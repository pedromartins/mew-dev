#include <unistd.h>
#include "drive_motor.h"
#include "arduino.h"
#include <iostream>

/*
 * This is an almost-not-quite-psuedo-code version
 * of the way I would solve last weeks goal
 *    (avoid a stationary box of a known size)
 * 
 * It is extremely hacky, but with a few simple helper functions
 * it will (...should) work.
 *
 * The idea behind these simple goals is, as we saw last wednesday,
 * to really get the subsystems working solidly.
 * We managed to diagnose a few issues with the arduinos and serial already
 * 
 * these should be easy to fix and make work for sunday
 *
 * Also, turns out you can actually do this simple task without threads at all....
 * ;-)
 */

using namespace std;

int initial_heading;
int current_heading;
int rotation;

int IR_readings[4];

Arduinos arduino;

int main(){
  arduino.open(SENSORS);
  init_drive_motor();
  set_drive_motor_power(HALF_FORWARDS, HALF_FORWARDS);
  
  do{
    arduino.getIR(IR_readings);
	usleep(50000);
	cout << IR_readings[0] << endl;
  }
  while( IR_readings[0] > 30);
  
  //start to spin clockwise on the spot
  set_drive_motor_power(HALF_FORWARDS, HALF_BACKWARDS);
  sleep(1);
  //and rotate 90 degrees
  rotation = 0;
  initial_heading = arduino.getCompass();
  cout << "initial_heading is " << initial_heading << endl;
  usleep(50000);

  while(rotation < 900){
    current_heading = arduino.getCompass();
    cout << "current_heading is " << current_heading << endl;
    if(current_heading > initial_heading){
      rotation = current_heading - initial_heading;
    }
    else{
      rotation = 3600 - ( initial_heading - current_heading);
    }
	cout << "Rotations is " << rotation << endl;
  }
 cin.get();
  //forwards again
  set_drive_motor_power(HALF_FORWARDS, HALF_FORWARDS);

  do{
    arduino.getIR(IR_readings);
	usleep(50000);
	cout << IR_readings[0] << endl;
  }
  while( IR_readings[1] > 30); //should be the left sensor

  
  //go a bit past the box, mmmmmmhackhackhackhack
  usleep(400000);
  
  //start to spin anti-clockwise on the spot
  set_drive_motor_power(HALF_BACKWARDS, HALF_FORWARDS);
  
  rotation = 0;
  current_heading = arduino.getCompass();
  while(rotation < 900){
    current_heading = arduino.getCompass();
    if(current_heading > initial_heading){
      rotation = 3600 - ( current_heading - initial_heading);
    }
    else{
      rotation = initial_heading - current_heading;
    }
  }


  set_drive_motor_power(HALF_FORWARDS, HALF_FORWARDS);
  
  sleep(3); //and we are hopefully around the box!
  
  set_drive_motor_power(STOP, STOP);
}
