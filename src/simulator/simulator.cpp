
#include "map.h"
#include "simulator.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define OUT_OF_BOARD "The robot went outside of the board!\n"
#define COLLISION "The robot collided with something!\n"
#define SUCCESS "Congratulations, task successful!\n Now go play with the simulator code :)\n"





void loadMap(int i) {
	mapNum = i;
}


/**
 * Returns a random double!
 */
double randDouble() {
	return rand()/((double)RAND_MAX + 1);
}

bool terminationCond() {
	return pos.x == dropArea[0] && pos.y == dropArea[1] && grab;
}

void SimulatedRobot::moveForward() {
	pos = inFront();
	if(!inBoard(pos)) {
		fail(OUT_OF_BOARD,TRUE);
	}
	if(!IS_EMPTY(pos)) {
		fail(COLLISION,TRUE);
	}
	if(grab && randDouble() < PROB_DROP_MOVING) {
		grab = FALSE;
		placePiece(pos.x, pos.y);
	}
	if(terminationCond()) {
		fail(SUCCESS, TRUE);
	}
}

void SimulatedRobot::pickUp() {
	Vector2di f = inFront();
	if(randDouble() > PROB_FAILURE_PICKUP && getElementAt(f) == PIECE ) {
		grab = TRUE;
		removePiece(f.x,f.y);
	}
}

Vector2di SimulatedRobot::getLocation() {
	return
}

void SimulatedRobot::turn(bool left) {
	if(left) {
		orientation = (orientation + 1) % 4;
	} else {
		orientation = (orientation + 3) % 4;
	}
}
