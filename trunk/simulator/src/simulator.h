
#ifndef SIMULATOR_H
#define SIMULATOR_H

/*
  mew Robot Simulator - 2009
  v.0.1 : Initial meeting 21/01/09
 */

#include "map.h"

#define PROB_FAILURE_PICKUP 0.1
#define PROB_DROP_MOVING 0.1

#define TRUE 1
#define FALSE 0
typedef int bool;

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

/*
  Load a different map 
  (must be done before starting/reseting)
*/
void loadMap(int i);

// Reset the board and robot
void restart();

#endif //SIMULATOR_H
