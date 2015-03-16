# Introduction #
Supposing that the robot can [localize](Localization.md) on a [virtual map](Mapping.md), then complete reasoning on that map to produce a sound [path](path.md), it is then necessary to interpret the path's nodes, inspect the current state of the robot, and produce a sensible acceleration and heading for the robot at any one time in the robot's execution.

# Concepts #
## Kinematics ##
A robot is an entity with speed and

# Approaches to Controlling Movement #
  * Hard coding - given that we have perfect information of the playing area and playing field, it would be totally unnecessary to do any special movement algorithms. Hard-coding a route to achieve tasks would suffice. Any plans are ignored.
  * Subsumption - a behaviour-oriented approach, to implement basic steering behaviours initially, (seek, flee, arrive, wander), and then build more complicated behaviours from delegating to lower-level behaviours (pursue, evade, path following, obstacle avoidance). This tiered design is modular, and allows for incremental testing.



# Paths #
Because the path produced by the A`*` algorithm will be very jagged (as the algorithm works on a set-resolution grid), it will be necessary to simplify the path, so that the robot may formulate make more generalized and sensible driving

## Simplification of paths ##


## Constraints ##

# Goals #

## Goal Channels ##