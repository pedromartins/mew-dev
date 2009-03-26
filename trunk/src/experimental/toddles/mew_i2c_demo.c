#include <unistd.h>
#include "mew_i2c.h"

//example i2c program
//shows how to use the mew_i2c library!
//gcc -o mew_i2c_demo mew_i2c.c mew_i2c_demo.c

//to initalise the library we need to know the device node
//for the usb-i2c device
//if this is the only device plugged in then it's probably
// "/dev/ttyUSB0"
//you can just grep /dev and have a look!

#define DEVICE_NODE "/dev/cu.usbserial-A2001nZa"

void loop();

int main(void){
  init_comms(DEVICE_NODE);
  loop();
  end_comms();
}

void loop(){
  int angle;
  for(angle = 135; angle > 50; angle-=5){
    //at the moment the only command is send_byte
    send_byte(MEW_DEV_ARDUINO_01, angle);
    sleep(1);
  }
    for(angle = 45; angle < 135; angle+=5){
    send_byte(MEW_DEV_SERVO_TEST, angle);
    sleep(1);
  }
}
