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
#include <boost/shared_ptr.hpp>
#include <map>

#include <core/core.h>

using namespace std;



/*
 * Here we try to put an experimental simulated robot into a simulated
 * world.
 *
 * We move the robot by one square, and see if the world reports that
 * to be the case.
 */
int main() {
	// typedef boost::shared_ptr<int> IntPtr;

	/*
	/// Temporarily tests unordered_map and hash for their behaviour,
	/// with shared_ptrs. Such that I can implement the virtual world properly.

	// Test1: A map type that maps (static) gridsquares (Vector2di) onto ints.
	typedef map<Vector2di *, int> VecValMap;

	VecValMap mappy;

	Vector2di *a = new Vector2di(10,6);
	Vector2di *b = new Vector2di(42,254);
	Vector2di *c = a;

	mappy[a] = 16;
	mappy[b] = 296;

	//Testing pointer equivalence.
	assert(mappy[a] == mappy[c]);


	// Maps a pointer of an IEntity to a number!
	typedef map<IEntity *, Staticio *> EntStatMap;

	EntStatMap entmap;

	SimpleVirtualRobot *rob = new SimpleVirtualRobot(NULL, Vector2di(0,0), NORTH);
	SimpleVirtualRobot *rob2 = new SimpleVirtualRobot(NULL, Vector2di(1,1), EAST);
	SimpleVirtualRobot *rob3 = rob;

	entmap[rob] = new Staticio(Vector2di(0,0), NORTH);
	entmap[rob3] = new Staticio(Vector2di(0,0), EAST);

	//Testing pointer equivalence.
	assert(entmap[rob] == entmap[rob3]);

	// Staticio teststat(Vector2di(24,15), SOUTH);

	// cout << teststat;


	for(EntStatMap::iterator i = entmap.begin(); i != entmap.end(); ++i) {
		cout << *(i->second) << endl;
	}
	*/

	VirtualWorld *vworld = new VirtualWorld();

	// The test world
	for(int i = 3; i != 6; i++) {
		for(int j = 0; j != vworld->getHeight() - 1 ; j++) {
			vworld->putPiece(i,j);
		}
	}
	vworld->putPiece(9,0);

	assert(vworld->getElementAt(Vector2di(9,0))!=EMPTY);

	// N.B Currently does nothing with initial data.
	SimpleVirtualRobot * robot = new SimpleVirtualRobot(vworld, Vector2di(0,0), SOUTH);
	Staticio stat(Vector2di(0,0), EAST);
	// put the robot into the world.
	vworld->putEntity(robot, stat);
	robot->moveForward(2);
	robot->turn(LEFT);
	robot->moveForward(6);

	// The robot should have been moved! XD
	assert(vworld->getPositionOf(robot) == Vector2di(2,6));

	cout << *vworld;

	// delete robot;

	return 0;
}
