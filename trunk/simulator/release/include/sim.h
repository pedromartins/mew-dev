#ifndef SIM_H
#define SIM_H

/*
  mew Robot Simulator - 2009
  v.0.1 : Initial meeting 21/01/09
 */

#define PROB_FAILURE_PICKUP 0.1
#define PROB_DROP_MOVING 0.1

#define TRUE 1
#define FALSE 0
typedef int bool;

typedef struct Position {
  int x;
  int y;
} Position;

// Get position from the sensors
Position getPosition();

// Is the robot holding something?
int isGrabbing();

// Move the robot forward
void moveForward();

// Pick up what's in *front* of the robot.
void pickUp();

// Turn 45º left or right
void turn(int left);

/*  Load a different map 
    (must be done before starting/reseting) */
void loadMap(int i);

// Reset the board and robot
void restart();

// **** MAP KNOWLEDGE ****
#define SIZE_X 10
#define SIZE_Y 10

typedef enum MapElement {
  EMPTY, PIECE, DROPZONE, FORBIDDEN
} MapElement;

MapElement getPos(Position pos);

#endif //SIM_H
