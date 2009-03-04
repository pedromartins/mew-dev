/*
 * gridmodel.h
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#ifndef GRIDMODEL_H_
#define GRIDMODEL_H_

/**
 * SimpleGridModel
 *
 * In a simple grid model, the robot and anything IN the grid is
 * simply represented by some enum value in a 2D array.
 * NOTE: this is a wrapper around the old simulator model.
 */
class GridModel {
	GridModel();

	virtual ~GridModel();

	void fail(char* msg, int fatal) {
		printf("At (%d,%d):\n", pos.x, pos.y);
		printf(msg);
		if(fatal)
			exit(0);
	}

	/**
	 * Returns true iff the position is on the board.
	 */
	bool inBoard(Vector2di newPos) {
		return (newPos.x >= 0 && newPos.x < SIZE_X &&
				newPos.y >= 0 && newPos.y < SIZE_Y);
	}

	Vector2di inFront() {
		Vector2di front;
		int * dir = frontDir[orientation];
		front.x = pos.x + dir[0];
		front.y = pos.y + dir[1];
		return front;
	}

	/**
	 * Clears the simulator
	 */
	void clear() {

	}
};

#endif /* GRIDMODEL_H_ */
