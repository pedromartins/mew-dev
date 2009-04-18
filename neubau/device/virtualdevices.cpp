/*
 * virtualdevices.cpp
 *
 *  Created on: 14-Apr-2009
 *      Author: fushunpoon
 */
#include "virtualdevices.h"

#include <math.h>
#include <iostream>

using namespace std;

void SimpleVirtualDrive::moveForward(int squares){
	Vector2di frontpos = world->inFront(payload);

	// stall when there is no place to go.
	if(!world->valid(frontpos) || !world->isEmpty(frontpos)) {
		cerr << "STALLING!!" << endl;
		return;
	}

	/* TODO REENABLE probablistic dropping mechanism
	if( robot->isGrabbing() && randDouble() < PROB_DROP_MOVING) {
		robot->grabbing = false;
		world->putPiece(pos.x, pos.y);
	} */

	world->setLocationOf(payload,
			world->getPositionOf(payload)+
			SimpleVirtualWorld::dOffsets[world->getOrientationOf(payload)]*squares
	);
}

/**
 * Turns the robot either left, right, or not at all.
 */
void SimpleVirtualDrive::turn(TurnDirection dir){
	if (dir != STRAIGHT) {
		world->setOrientationOf(payload,
				(Orientation)(((int)world->getOrientationOf(payload)+dir)%4)
		);
	}
}


/**
 * Closes the claw in the virtual world.
 */
void SimpleVirtualClaw::close(){
	Vector2di frontpos = world->inFront(mountpoint);

	/* TODO REENABLE probablistic pickup failure.
	if(randDouble() > PROB_FAILURE_PICKUP &&
			world->getElementAt(frontpos) == PIECE ) {
		robot->grabbing = true;
	}*/

	if (world->getElementAt(frontpos) == PIECE) {
		world->removePiece(frontpos.x,frontpos.y);
		holding = true;
	}

	closed = true; // the claw will always succeed in closing.
}

/**
 * Opens the claw and drops a piece (if holding!) in the simulated world.
 * If in the simulated world, the robot is facing a square that is
 * FORBIDDEN, or if another piece is already placed there, then the
 * piece being held will be LOST.
 */
void SimpleVirtualClaw::open(){
	Vector2di frontpos = world->inFront(mountpoint);

	/* TODO REENABLE probablistic pickup failure.
	if(randDouble() > PROB_FAILURE_PICKUP &&
			world->getElementAt(frontpos) == PIECE ) {
		robot->grabbing = true;
	}*/

	if (world->getElementAt(frontpos) == EMPTY) {
		world->putPiece(frontpos.x,frontpos.y);
	}

	holding = false; // holding will definitely be terminated.
	closed = false;  // closed with definitely be terminated.
}
