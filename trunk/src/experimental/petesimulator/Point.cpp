#include "Point.h"

Point::Point(double x, double y){
	xVal = x;
	yVal = y;
}

Point::~Point(void)
{
}


double Point::dist(Point other) {
    double  xd = xVal - other.xVal;
    double yd = yVal - other.yVal;
    return sqrt(xd*xd + yd*yd);
}

// Add or subtract two points.
Point Point::add(Point b){
	return Point(xVal + b.xVal, yVal + b.yVal);
}
Point Point::sub(Point b){
	return Point(xVal - b.xVal, yVal - b.yVal);
}

// Move the existing point.
void Point::move(double x, double y){
	xVal += x;
	yVal += y;
}

int Point::sdl_x(){
	return (int)((xVal + 0.5) * SCALING_FACTOR);
}

int Point::sdl_y(){
	return (int)((yVal + 0.5) * SCALING_FACTOR);
}