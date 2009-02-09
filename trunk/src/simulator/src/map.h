
#ifndef MAP_H
#define MAP_H

#define IS_EMPTY(pos) getElementAt(pos) == EMPTY

#define SIZE_X 10
#define SIZE_Y 10

/**
 * Enum type for representing a drop zone.
 */
typedef enum MapElement {
  EMPTY, PIECE, DROPZONE, FORBIDDEN
} MapElement;

/**
 * An integral position type
 */
typedef struct Position {
  int x;
  int y;
} Position;

void initMap();

/**
 * Prepares a predefined map.
 * @param mapNum The predefined map's number.
 */
void initPredefMap(int mapNum);


/**
 * Returns the map element at a particular position.
 * @param pos the position
 */
MapElement getElementAt(Position pos);

/**
 * Places a piece onto the map.
 * @param posx The x coordinate
 * @param posy The y coordinate
 */
void placePiece(int posx, int posy);

/**
 * Removes a piece from the map.
 * @param posx
 * @param posy
 */ 
void removePiece(int posx, int posy);

#endif //MAP_H
