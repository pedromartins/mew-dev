#ifndef MAP_H
#define MAP_H

#define SIZE_X 10
#define SIZE_Y 10

#include <vector2d.h>

using namespace std;
using namespace mew::core;

/**
 * Enum type for representing a drop zone.
 */
typedef enum MapElement {
  EMPTY, PIECE, DROPZONE, FORBIDDEN
} MapElement;


/**
 * Map
 *
 * A map is a simplified grid-based repr
 */
class Map : public IGridEntityModel {
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

private:
	MapElement map[SIZE_X][SIZE_Y];
};


#endif //MAP_H
