
#ifndef MAP_H
#define MAP_H

#define IS_EMPTY(pos) getPos(pos) == EMPTY

#define SIZE_X 10
#define SIZE_Y 10

typedef enum MapElement {
  EMPTY, PIECE, DROPZONE, FORBIDDEN
} MapElement;

typedef struct Position {
  int x;
  int y;
} Position;

void initMap();

void initPredefMap(int mapNum);

MapElement getPos(Position pos);

void placePiece(int posx, int posy);

void removePiece(int posx, int posy);

#endif //MAP_H
