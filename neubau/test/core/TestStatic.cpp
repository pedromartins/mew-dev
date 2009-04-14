
// Use assertions to let this test FAIL if a condition is not met.
#include <assert.h>
#include <core/core.h>
#include <iostream>

using namespace std;


/**
 * TODO COMPLETE this test!!!!
 * @return
 */
int main() {
	Static s1(6,2);
	Static s2(3,5);

	// Test the equivalence operator
	assert(s1 == Static(6,2));


	// Test that the getOrientationAsVector method returns a unit vector pointing in the
	// right way.
	assert(s1.getOrientationAsVector() == Vector2df(6,2).unit());


	// Test that setOrientation
	Vector2df v1(1,0);
	s2.setOrientationFromVelocity(v1);


	// Test the clear method actually clears s1's position vector. (sets to zero)
	s1.clear();
	assert(s1.position == Vector2df());

	return 0;
}

