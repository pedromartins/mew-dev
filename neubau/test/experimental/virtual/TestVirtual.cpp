/*
 * TestVirtual.cpp
 *
 *  Created on: 14-Apr-2009
 *      Author: fushunpoon
 */
#include <iostream>
#include <experimental/virtual/virtualworld.h>
#include <experimental/profile/simpleprofile.h>

#include <assert.h>

using namespace std;

/*
 * Here we try to put an experimental simulated robot into a simulated
 * world.
 *
 * We move the robot by one square, and see if the world reports that
 * to be the case.
 */
int main() {
	VirtualWorld vworld;

	// The test world
	for(int i = 3; i != 6; i++) {
		for(int j = 0; j != vworld.getHeight() - 1 ; j++) {
			vworld.putPiece(i,j);
		}
	}

	vworld.putPiece(9,0);


	assert(vworld.getElementAt(Vector2di(9,0))!=EMPTY);

	// N.B Currently does nothing with initial data.
	SimpleVirtualRobot robot(&vworld, Vector2di(0,0), SOUTH);


	// put the robot into the world.
	vworld.putEntity(EntityPtr(&robot), StaticioPtr(new Staticio(Vector2di(0,0), EAST)));

	cout << "Put the entity into the vworld." << endl;
	robot.moveForward(2);
	cout << "Completed the move forward" << endl;
	// The robot should have been moved! XD
	assert(vworld.getPositionOf(EntityPtr(&robot)) == Vector2di(2,0));

	// cout << vworld;
}
