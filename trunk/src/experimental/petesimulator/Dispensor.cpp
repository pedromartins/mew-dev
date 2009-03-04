#include "Dispensor.h"

Dispensor::Dispensor(bool col, int cyl)
{
	//Initialise with number of cylinders
	cylinders = cyl;
	color = col;
	realSize = new Point(80,80);
}

Dispensor::~Dispensor(void)
{
}

