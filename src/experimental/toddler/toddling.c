#include <unistd.c>
#include "drive_motor.h"
//#include "the next iteration of udev'ed arduino drivers

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


int compass_reading;

int main(){
  init_motor_driver();
  set_drive_motor_power(HALF_FORWARD, HALF_FORWARDS);
  
  while(get_IR_reading(FRONT) > 30){
    //do nothing, the get_IR_reading method should ensure it
    //doesn't overload the serial buffers
    ;
  }
  
  //start to spin clockwise on the spot
  set_drive_motor_power(HALF_FORWARD, HALF_BACKWARDS);
  
  /*
   * this is more psuedo-ey, but should be easy to implement!
   */
  compass_reading = get_compass_reading();
  while(abs(compass_reading, get_compass_reading()) < 900){;} //yes, i said psuedo
  
  //forwards again
  set_drive_motor_power(HALF_FORWARD, HALF_FORWARDS);
  while(get_IR_reading(LEFT) < 50){;}
  
  //go a bit past the box, mmmmmmhackhackhackhack
  usleep(400000);
  
  //start to spin anti-clockwise on the spot
  set_drive_motor_power(HALF_BACKWARDS, HALF_FORWARD);
  
  compass_reading = get_compass_reading();
  while(abs(compass_reading, get_compass_reading()) < 900){;}
  
  set_drive_motor_power(HALF_FORWARD, HALF_FORWARDS);
  
  sleep(3); //and we are hopefully around the box!
  
  set_drive_motor_power(STOP, STOP);
}