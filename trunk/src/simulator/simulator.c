
#include "map.h"
#include "simulator.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define OUT_OF_BOARD "The robot went outside of the board!\n"
#define COLLISION "The robot collided with something!\n"
#define SUCCESS "Congratulations, task successful!\n Now go play with the simulator code :)\n"

// counter-clockwise
typedef enum Orientation {
  NORTH, WEST, SOUTH, EAST
} Orientation;

// State:
Position pos;
int orientation;
int grab;

//                     NORTH  SOUTH   EAST    WEST
int frontDir[4][2] = { {0,1}, {-1,0}, {0,-1}, {1,0} };
int dropArea[] = {4,0};
bool inited = FALSE;
int mapNum = 0;

Position getPosition() {
  return pos;
}

int isGrabbing() {
  return grab;
}

void loadMap(int i) {
  mapNum = i;
}

void initSimulator() {
  if(!inited) {
    srand(time(0));
    initPredefMap(mapNum);
    placePiece(SIZE_X-1, 0);
    pos.x = 0;
    pos.y = 0;
    orientation = NORTH;
    grab = FALSE;
    inited = TRUE;
  }
}

void restart() {
  inited = FALSE;
  initSimulator();
}

void fail(char* msg, int fatal) {
  printf("At (%d,%d):\n", pos.x, pos.y);
  printf(msg);
  if(fatal)
    exit(0);
}

bool inBoard(Position newPos) {
  if( newPos.x >= 0 && newPos.x < SIZE_X &&
      newPos.y >= 0 && newPos.y < SIZE_Y   ) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

Position inFront() {
  Position front;
  int * dir = frontDir[orientation];
  front.x = pos.x + dir[0];
  front.y = pos.y + dir[1];
  return front;
}

double randDouble() {
  return rand()/((double)RAND_MAX + 1);
}

bool terminationCond() {
  return pos.x == dropArea[0] && pos.y == dropArea[1] && grab;
}

void moveForward() {
  initSimulator();
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
  
void pickUp() {
  initSimulator();
  Position f = inFront();
  if(randDouble() > PROB_FAILURE_PICKUP && getElementAt(f) == PIECE ) {
    grab = TRUE;
    removePiece(f.x,f.y);
  }
}

void turn(bool left) {
  initSimulator();
  if(left) {
    orientation = (orientation + 1) % 4;
  } else {
    orientation = (orientation + 3) % 4;
  }
}
