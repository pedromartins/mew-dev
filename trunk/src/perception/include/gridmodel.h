/*
 * gridmodel.h
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#ifndef GRIDMODEL_H_
#define GRIDMODEL_H_

#include <core.h>

using namespace mew;
using namespace core;

/**
 * GridModel
 *
 * In a simple grid model, the robot and anything IN the grid is
 * simply represented by some enum value in a 2D array.
 *
 * NOTE: this is a wrapper around the old simulator model.
 */
class GridModel {
	GridModel();

	virtual ~GridModel();

	Map(int mapNum = 0);
	virtual ~Map() {}

	/**
	 * Returns the map element at a particular position.
	 * @param pos the position
	 */
	MapElement getElementAt(Vector2di pos){
		return map[pos.x][pos.y];
	}
	MapElement getElementAt(int posx, int posy){
		return map[posx][posy];
	}

	/**
	 * Puts a piece onto the map.
	 * @param posx The x coordinate
	 * @param posy The y coordinate
	 */
	void putPiece(int posx, int posy) {
		map[posx][posy] = PIECE;
	}

	/**
	 * Removes a piece from the map.
	 * @param posx
	 * @param posy
	 */
	void removePiece(int posx, int posy){
		map[posx][posy] = EMPTY;
	}

	/**
	 * Removes all the pieces.
	 */
	void clear() {
		// TODO
	}

private:
	MapElement map[SIZE_X][SIZE_Y];

};

#endif /* GRIDMODEL_H_ */
