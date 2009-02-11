
#define PROLOG_MODULE "user"

#define PL_CAST(type,term) ((type *)((void*)(term)))
#include "SWI-cpp.h"

#include <iostream>

using namespace std;

PREDICATE(hello,1)
{
	cout << "Hello " << (char *)A1 << endl;
	
	return TRUE;
}

class Point2df {
public:
	Point2df(float x, float y): _x(x), _y(y) {}

	float _x;
	float _y;
};

/**
 * Defines a box.
 */
class Box {
public:
	Box(Point2df point, float w, float h)
	: pos(point), width(w), height(h) {}
	virtual ~Box() {}
	float getArea() { return width * height; }
	
	Point2df pos;
	float width;
	float height;
};

PREDICATE(getTheBox,1)
{
	return A1 = (void *) new Box(Point2df(0,0),60,45);
}

/**
 * Returns the area of the box.
 * Wrapper around Box::getArea();
 */
PREDICATE(getArea,2)
{
	Box* box = PL_CAST(Box,A1);
	return A2 = box->getArea();
}
