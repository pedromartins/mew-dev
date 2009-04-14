
// Use assertions to let this test FAIL if a condition is not met.
#include <assert.h>
#include <core/core.h>
#include <iostream>

using namespace std;

int main() {
	Vector2df zero(0,0);
	Vector2df v1(92,52);
	Vector2df v2(-1.52,5.52);

	// Test the equality operator works (for other
	assert(v1 == Vector2df(92,52));
	assert(v2 == Vector2df(-1.52,5.52));

	// Test the add operator
	Vector2df v3 = v1 + v2;
	assert( fequals(v3.x,90.48) && fequals(v3.y,57.52));

	// Test the subtraction operator
	v3 = v1 - v2;
	assert( fequals(v3.x,93.52) && fequals(v3.y,46.48));

	// Test the magnitude function.
	assert( fequals(zero.magnitude(),0.0f));

	// Test the squared magnitude function.
	assert( fequals(v1.squareMagnitude(), 92*92 + 52*52));

	// Test clear() and its affect in terms of equivalence with zero vector
	v2.clear();
	assert( v2 == zero);

	// Test unit vector actually returns a UNIT vector.
	assert( fequals(v1.unit().magnitude(),1.0f) );

	// Test the unit vector of a zero vector is a zero vector.
	assert( zero.unit() == zero );

	return 0;
}

