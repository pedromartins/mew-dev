/**

mew-robotics

Provides predicates for positioning and orienting the robot
via movement of the entire robot.

Most functions ensure the arrival of the robot at some location
specified if the predicate succeeds.
However, if the robot is unable to get to the location after
some certain time limit, then the movement is considered to have failed.

Uses movement to move to appropriate places.

@author Hok Shun Poon 
*/



in_front_of_lintel:-
  % TODO