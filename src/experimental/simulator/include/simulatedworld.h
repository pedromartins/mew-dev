#ifndef SIMULATEDWORLD_H
#define SIMULATEDWORLD_H

#include <core.h>

#define DEFAULT_SIZE 10

/**
 * SimulatedWorld
 *
 * In a simple grid model, the robot and anything IN the grid is
 * simply represented by some enum value in a 2D array.
 *
 * NOTE: this is a wrapper around the old simulator model.
 */
class SimulatedWorld {
	SimulatedWorld(int map);
	SimulatedWorld(int width, int height);
	virtual ~SimulatedWorld();

	/**
	 * Returns the map element at a particular position.
	 * @param pos the position
	 */
	MapElement getElementAt(Vector2di pos)
	{
		return map[pos.x][pos.y];
	}

	MapElement getElementAt(int posx, int posy)
	{
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
		memset(map,EMPTY,width*height*sizeof(MapElement));
	}

private:
	int width;
	int height;
	MapElement map[][];
};



#endif //MAP_H
