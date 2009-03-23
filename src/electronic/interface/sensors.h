#ifndef SENSORSH
#define SENSORSH
//sensor wrapper functions

typedef struct
{
	int ir0, ir1, ir2, ir3;
} IRreadings;

IRreadings* getIRreadings(int arduino_fd);
int getCompassreading(int arduino_fd);

#endif
