#include <unistd.h>
#include "drive_motor.h"
#include "arduino.h"

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

Arduino arduino;

int main(){
  arduino.init();
  init_drive_motor();
  set_drive_motor_power(HALF_FORWARDS, HALF_FORWARDS);
  
  do{
    arduino.getIRreadings(IR_readings);
  }
  while( IR_readings[0] > 30);
  
  //start to spin clockwise on the spot
  set_drive_motor_power(HALF_FORWARDS, HALF_BACKWARDS);

  //and rotate 90 degrees
  rotation = 0;
  initial_heading = arduino.getCompassreading();
  while(rotation < 900){
    current_heading = arduino.getCompassreading();
    if(current_heading > initial_heading){
      rotation = current_heading - initial_heading;
    }
    else{
      rotation = 3600 - ( initial_heading - current_heading);
    }
  }
  
  //forwards again
  set_drive_motor_power(HALF_FORWARDS, HALF_FORWARDS);

  do{
    arduino.getIRreadings(IR_readings);
  }
  while( IR_readings[1] > 30); //should be the left sensor

  
  //go a bit past the box, mmmmmmhackhackhackhack
  usleep(400000);
  
  //start to spin anti-clockwise on the spot
  set_drive_motor_power(HALF_BACKWARDS, HALF_FORWARDS);
  
  rotation = 0;
  current_heading = arduino.getCompassreading();
  while(rotation < 900){
    current_heading = arduino.getCompassreading();
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
