# Introduction #
Initially, the location of the robot will be known by the robot, because we would have had to place it in one of two starting areas; both areas are well defined spaces in the map.


# Approaches #
## Feature-finding and Landmarks (Beacons) ##
## Monte Carlo Localization ##
Having perfect knowledge of the map, the idea of Monte Carlo is simple: Random points are placed on a software model of the map; and theoretical sensor readings at those random locations are computed. Samples from the actual sensors are taken, and is compared against the theoretical sensor readings from each random point. If for some points, the theoretical and real readings yield high correlation, it is quite likely that the robot is near that random location. Further tests are done on a random area around that particular point.

The Monte-Carlo method could be computationally expensive.
Bayesian inference ftw! :D


# Details #