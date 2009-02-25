#pragma once
#include "Common.h"
#include "Board.h"
#include "Cylinder.h"


class Robot{
	public:
	Point *CentreOfRotation;
	Point *FrontLeft;
	Point *FrontRight;
	Point *RearLeft;
	Point *RearRight;
	double direction;
	//stores size in mm
	Point *realSize;
	//stores position of robot, according to it's centre of rotation
	Point *pos;
	//Velocities
	double xVel, yVel;
	//Holds cylinders carried
	Cylinder cylinders[5];
	//Boolean to see if it holds a lentil
	bool lentil;
	SDL_Surface *pic;
	void handle_input(SDL_Event *event);
	void move(Board *field);
	void rotate(double angle);
	Robot();
	~Robot();
};


