
#include <stdio.h>
#include "sim.h"

void printStatus(){
  printf("Robot at position (%d,%d)!\n", getPosition().x, getPosition().y);
  if(isGrabbing()) printf("Grabbing!\n");
}

int main() {
  //loadMap(1);
  printStatus();
  int i;
  // The robot will be initialized at (0,0) facing NORTH
  for(i = 1; i != SIZE_Y ; i++) {
    moveForward();
    printStatus();
  }
  turn(FALSE); // turn right => facing EAST
  for(i = 1; i != SIZE_X; i++) {
    moveForward();
    printStatus();
  }
  turn(FALSE); // turn right => facing SOUTH
  for(i = 1; i != SIZE_X; i++) {
    moveForward();
    pickUp();
    printStatus();
  }
  turn(FALSE); // turn right => facing WEST
  for(i = 1; i != SIZE_X; i++) {
    moveForward();
    printStatus();
  }
  printf("Finished!"); 
  return 0;
}
