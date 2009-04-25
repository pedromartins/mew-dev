/*
 * TestVirtualWorld.cpp
 *
 *  Created on: 18-Apr-2009
 *      Author: fushunpoon
 */

#include <iostream>
#include <experimental/virtual/virtualworld.h>

#include <assert.h>

int main() {
	// typedef boost::shared_ptr<int> IntPtr;


	SimpleVirtualWorld *vworld = new SimpleVirtualWorld();

	// The test world
	for(int i = 3; i != 6; i++) {
		for(int j = 0; j != vworld->getHeight() - 1 ; j++) {
			vworld->putPiece(i,j);
		}
	}
	vworld->putPiece(9,0);

	cerr << *vworld;

	return 0;
}
