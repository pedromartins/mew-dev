#include <math.h>
#include "robotArm.h"
#include <iostream>

using namespace std;

#define PI (3.141592653589793)

robotArm::robotArm() 
{
	length[0] = 200;
	length[1] = 200;
	position[BASE].x = 0;
	position[BASE].y = 0;

	position[ELBOW].x = 0;
	position[ELBOW].y = 50;
	
	position[HAND].x = -50;
	position[HAND].y = 50;

	setPosition(-60,60);

}


void robotArm::changeAngle(int angleNum, int inAngle) 
{
	//Change angle and update positions
	angle[angleNum] = inAngle;

	position[ELBOW].x = position[BASE].x - length[0]*cos(angle[SHOULDER]*PI/180);
	position[ELBOW].y = position[BASE].y + length[0]*sin(angle[SHOULDER]*PI/180);

	position[HAND].x = position[ELBOW].x - length[1]*cos((180-angle[SHOULDER]+angle[ELBOW])*PI/180);
	position[HAND].y = position[ELBOW].y + length[1]*sin((180-angle[SHOULDER]+angle[ELBOW])*PI/180);
}

void robotArm::setPosition(float x,float y) 
{
	float grad;
	position[HAND].x = x;
	position[HAND].y = y;
	
	if ((position[HAND].x-position[ELBOW].x) > 0) {
		grad = (position[HAND].y - position[ELBOW].y)/(position[HAND].x-position[ELBOW].x);
		position[ELBOW].x = position[HAND].x - length[1]*cos(atan(grad));
		position[ELBOW].y = position[HAND].y - length[0]*sin(atan(grad));
	} else 	if ((position[HAND].x-position[ELBOW].x) < 0) {
		grad = (position[HAND].y - position[ELBOW].y)/(position[HAND].x-position[ELBOW].x);
		position[ELBOW].x = position[HAND].x + length[1]*cos(atan(grad));
		position[ELBOW].y = position[HAND].y + length[0]*sin(atan(grad));
	}

	if ((position[BASE].x-position[ELBOW].x) > 0) {
		grad = (position[BASE].y - position[ELBOW].y)/(position[BASE].x-position[ELBOW].x);
		position[ELBOW].x = position[BASE].x - length[1]*cos(atan(grad));
		position[ELBOW].y = position[BASE].y - length[0]*sin(atan(grad));
	} else 	if ((position[BASE].x-position[ELBOW].x) < 0) {
		grad = (position[BASE].y - position[ELBOW].y)/(position[BASE].x-position[ELBOW].x);
		position[ELBOW].x = position[BASE].x + length[1]*cos(atan(grad));
		position[ELBOW].y = position[BASE].y + length[0]*sin(atan(grad));
	}

	if ((position[ELBOW].x-position[HAND].x) > 0) {
		grad = (position[ELBOW].y - position[HAND].y)/(position[ELBOW].x-position[HAND].x);
		position[HAND].x = position[ELBOW].x - length[1]*cos(atan(grad));
		position[HAND].y = position[ELBOW].y - length[0]*sin(atan(grad));
	} else 	if ((position[ELBOW].x-position[HAND].x) < 0) {
		grad = (position[ELBOW].y - position[HAND].y)/(position[ELBOW].x-position[HAND].x);
		position[HAND].x = position[ELBOW].x + length[1]*cos(atan(grad));
		position[HAND].y = position[ELBOW].y + length[0]*sin(atan(grad));
	}

	angle[ELBOW] = 180*acos((position[ELBOW].x*(position[HAND].x-position[ELBOW].x)+position[ELBOW].y*(position[HAND].y-position[ELBOW].y))/
									(length[0]*length[1]))/PI;
	angle[SHOULDER] = 180*acos((position[ELBOW].x*(-1))/(length[0]))/PI;

}
