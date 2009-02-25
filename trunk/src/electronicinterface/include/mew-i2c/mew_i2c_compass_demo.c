#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "mew_i2c.h"

//example i2c program
//shows how to use the mew_i2c library!
//gcc -o mew_i2c_demo mew_i2c.c mew_i2c_demo.c

//to initalise the library we need to know the device node
//for the usb-i2c device
//if this is the only device plugged in then it's probably
// "/dev/ttyUSB0"
//you can just grep /dev and have a look!

#define DEVICE_NODE "/dev/ttyUSB0"

uint16_t heading[1];

void loop();

int main(void){
  init_comms(DEVICE_NODE);
  loop();
  end_comms();
}

void loop(){
	send_byte(COMPASS, 'A');
	usleep(10000);
	read_bytes(COMPASS, 2, heading);
	printf("heading: %hx\n", *heading);
}
