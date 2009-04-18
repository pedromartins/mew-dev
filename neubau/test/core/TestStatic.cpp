
// Use assertions to let this test FAIL if a condition is not met.
#include <assert.h>
#include <core/core.h>
#include <iostream>
#include <sstream>


using namespace std;

typedef Static<int, Orientation> Staticio;


/**
 * TODO COMPLETE this test!!!!
 * @return
 */
int main() {
	Staticio s1(6,2,NORTH);
	Staticio s2(Vector2di(251,-143), SOUTH);

	// Test the equivalence operator
	assert(s1 == Staticio(6,2,NORTH));

	// Test that the << operator works.
	stringstream ss;
	ss << s1;
	assert(ss.str().compare("{(6,2),0}")==0);

	// Test that the getOrientationAsVector method returns a unit vector pointing in the
	// right way.

	// TODO retrive orientation as vector.
	// assert(s1.getOrientationAsVector() == Vector2df(6,2).unit());


	// Test that setOrientation
//	Vector2df v1(1,0);
//	s2.setOrientationFromVelocity(v1);


	// Test the clear method actually clears s1's position vector. (sets to zero)
	s1.clear();
	assert(s1.position == Vector2di() && s1.orientation==0);

	return 0;
}

