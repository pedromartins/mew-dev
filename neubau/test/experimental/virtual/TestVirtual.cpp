/*
 * TestVirtual.cpp
 *
 *  Created on: 14-Apr-2009
 *      Author: fushunpoon
 */
#include <iostream>
#include <experimental/virtual/virtualworld.h>
#include <experimental/profile/simpleprofile.h>

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

	SimpleVirtualRobot robot(&vworld, Vector2di(0,0), SOUTH);

	robot.moveForward(2);

	cout << vworld;
}
