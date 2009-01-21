
#include "map.h"

#include <stdio.h>
#include <stdlib.h>

MapElement map[SIZE_X][SIZE_Y];

void initMap() {
  int i,j;
  for(i = 0; i != SIZE_X; i++) {
    for(j = 0; j != SIZE_Y; j++) {
      map[i][j] = EMPTY;
    }
  }
}

void initPredefMap(int mapNum) {
  switch(mapNum) {
  case 0:
    initMap();
    printf("initMap: Map 0 chosen!");
    break;
  case 1:
    initMap();
    printf("initMap: Map 1 chosen!");
    int i, j;
    for(i = 3; i != 6; i++) {
      for(j = 0; j != SIZE_Y - 1 ; j++) {
	map[i][j] = FORBIDDEN;
      }
    }
    placePiece(9,0);
    break;
  default:
    printf("initMap: No such map available!\n");
    exit(0);
  }
}

MapElement getPos(Position pos) {
  return map[pos.x][pos.y];
}

void placePiece(int posx, int posy) {
  map[posx][posy] = PIECE;
}

void removePiece(int posx, int posy) {
  map[posx][posy] = EMPTY;
}
