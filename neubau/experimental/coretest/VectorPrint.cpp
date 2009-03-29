#include <iostream>

#include "static.h"
#include "vector2d.h"
#include "kinematic.h"

using namespace std;

// typedef Static<float,double> StaticFD

int main()
{
	Vector2di i(0,0);

	Static s();
	Kinematic k();

	cout << "I would like you to meet the Null vector!!" <<endl;
	cout << i << endl;
	cout << "Isn't he gorgeous?" << endl;

	return 0;
}
