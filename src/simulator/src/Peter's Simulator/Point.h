#pragma once
#include "Common.h"
#include <math.h>

class Point
{
private:
	double xVal,yVal;
public:
	// Extractors.
	double x() { return xVal; }
	double y() { return yVal; }
	int sdl_x();
	int sdl_y();
	double dist(Point other);
	Point add(Point b);
	Point sub(Point b);
	void move(double x, double y);
	Point(double x, double y);
	~Point(void);
};
