#include "mew_i2c.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

static int fd;

void init_comms(const char * device_node){
	struct termios current_tios;
	struct termios new_tios;

	printf("opening device\n");	
	//open the device
	if((fd = open(device_node, O_RDWR | O_NOCTTY)) < 0)
		perror("error opening device");
	
	//set up the serial port attributes
	tcgetattr(fd, &current_tios); //save the current setting

	bzero(&new_tios, sizeof(new_tios));

	new_tios.c_cflag |= B19200 | CREAD | CS8 | CSTOPB;

	//these should be all the settings we need

	tcflush(fd, TCIFLUSH);

	tcsetattr(fd, TCSANOW, &new_tios);

	printf("opened device sucessfully\n");
}

void end_comms(){
  close(fd);
}

void send_byte(int addr, char byte_to_send){
	char* message;

	message = malloc(3);
	//create the message:
	message[0] = I2C_SGL;
	message[1] = (addr << 1);
	message[2] = byte_to_send;

	printf("writing message\n");
	//write a message
	if((write(fd, message, 3)) < 0)
		perror("writing to device");

	free(message);
}

//could maybe make this a bit safer, byte array!
void write_byte_to_register(int addr, int reg, char command){
	char* message;

	message = malloc(5);
	//create the message:
	message[0] = I2C_CMD;
	message[1] = (addr); //they didn't specify the address right, no shifting!
	message[2] = reg; //the register to write to
	message[3] = 0x01; //number of bytes to follow
	message[4] = command; //the command!

	printf("writing message\n");
	//write a message
	if((write(fd, message, 5)) < 0)
		perror("writing to device");

	free(message);
}


/*
 * Read multiple bytes from a device (not internal registers)
 */
void read_bytes(uint8_t addr, uint8_t bytes, void* retbuf){
        uint8_t message[3];

        //create the message:
        message[0] = I2C_MUL;
        message[1] = (addr << 1 | 0x01); //OR with the read bit
        message[2] = bytes; //number of bytes to read

        printf("writing message\n");
        //write a message
        if( (write(fd, message, 3)) < 0 ){
                perror("writing to device");
	}

	usleep(10000); //try this

	printf("reading message\n");
	if((read(fd, retbuf, bytes)) < 0){
		perror("reading from device");
	}
	
}
