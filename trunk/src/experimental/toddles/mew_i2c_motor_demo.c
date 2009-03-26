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

#define DEVICE_NODE "/dev/ttyUSB1"

#include <unistd.h>


void loop();

int main(void){
	init_comms(DEVICE_NODE);
	loop();
	end_comms();
}

void loop(){
	int speed;
	for(speed = 130; speed < 240; speed+=5){
		write_byte_to_register(WHEEL_MOTOR_CONTROLLER, WHEEL_MOTOR_CONTROLLER_LEFT_SPEED, speed);
		usleep(1000000);
	}
	for(speed = 240; speed > 10; speed-=5){
		write_byte_to_register(WHEEL_MOTOR_CONTROLLER, WHEEL_MOTOR_CONTROLLER_LEFT_SPEED, speed);
		usleep(1000000);
	}
	for(speed = 10; speed < 130; speed+=5){
		write_byte_to_register(WHEEL_MOTOR_CONTROLLER, WHEEL_MOTOR_CONTROLLER_LEFT_SPEED, speed);
		usleep(1000000);
	}
}
