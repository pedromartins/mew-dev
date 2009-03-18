/*
 * simulateddevices.cpp
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#include <simulateddevices.h>

using namespace std;

virtual void SimulatedDriveSystem::moveFoward(int squares){
	Vector2di frontpos =
		world->inFront(robot->getPosition(), robot->getOrientation());

	if(!world->valid(frontpos || !world->isEmpty(frontpos))) {
		cout << "STALLING!!" << endl;
	}

	/*
	 * TODO re-enable probability of dropping a piece.
	if( robot->isGrabbing() && randDouble() < PROB_DROP_MOVING) {
		robot->grabbing = false;
		world->putPiece(pos.x, pos.y);
	} */

	world->setLocationOf(robot,
			world->getLocationOf(robot)+
			frontDir[world->getOrientationOf(robot)]*squares
	);
}

/**
 * Turns the robot either left, right, or not at all.
 */
virtual void SimulatedDriveSystem::turn(TurnDirection dir){
	if (dir != STRAIGHT) {
		world->setOrientationOf(robot,
				(world->getOrientationOf(robot)+
						dir)%4
		);
	}
}


/**
 * Picks up a piece in the simulated world.
 */
void SimulatedClaw::pickup(){
	Vector2di frontpos = world->inFront(robot->getPosition(),robot->getOrientation());

	if(randDouble() > PROB_FAILURE_PICKUP &&
			world->getElementAt(frontpos) == PIECE ) {
		robot->grabbing = true;
		world->removePiece(frontpos.x,frontpos.y);
	}

}
