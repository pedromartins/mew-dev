# Introduction #
Dead reckoning and odometry is concerned with tracking the state of the robot through 'internal' sensors only, without external references. 'Internal' sensors are those that do not take information from the world; they are, instead, sensors that report on the state of the robot's components. These include:

  * Angle of servos
  * Angular speed of servos
  * Angular speed of motors
  * Maximum known acceleration of motors/servos
  * Size of the robot's wheel
  * Compass reading

It is important to keep this information, and later combine (using weighted blending techniques) with other sensory data, to refine an estimate of our robot's location.

# Approaches #
Due to the nature of our robot's arbitarily changing velocity, the problem of finding an accurate estimate of the robot's absolute position could be thought of as the solution to an integral of the velocity, on both x and y axes.

If we did numerical integration on the velocity, this yields a solution only if the function in question is defined (e.g. constant speed). However, because our velocity is some random function of time (this function is generated arbitarily by the control system), to compute the position, we must employ numerical methods of integrating over small discrete time-steps, each of length _dt_ milliseconds. Below are several methods of doing so.

## First order methods ##
First-order methods give us a quick and dirty, computationally cheap

### Euler Method ###
http://en.wikipedia.org/wiki/Euler_method
The Euler method simply takes the current velocity, assumes it remains constant throughout _dt_. i.e., the velocity function is approximated by a linear line segments. This method of approximation is rather naive, and only works well if time-steps are very fine.

### Midpoint Method ###
http://en.wikipedia.org/wiki/Midpoint_method

## Second order methods ##
Second-order methods consider second-order differential equations; this is useful in our case if we wish to incorporate the acceleration into our odometric estimation. Acceleration itself could be provided by some function of time.

### Beeman's algorithm ###
http://en.wikipedia.org/wiki/Beeman%27s_algorithm
Computationally expensive, but error corrections allow for a more accurate estimate.

### Verlet Integration ###
http://en.wikipedia.org/wiki/Verlet_integration
An integration technique used specifically for Newtonian equations of motion. May not be relevant.

**We should use Beeman's algorithm to update both velocities and positions, AND angular velocities, and orientations.**

Here is a nice paper that I think everybody should read, about differential steering (which is exactly what we're using).
http://rossum.sourceforge.net/papers/DiffSteer/

There are competitions for robots which are exceptional at this type of the thing. The task is generally to do 1 lap of a circuit and finish as close to the starting position as possible, with no external sensors. They often call it 'dead-reckoning'. [This](http://www.seattlerobotics.org/encoder/200108/using_a_pid.html) seems like it could be a good article. And you'll find lots more information [here](http://www.google.co.uk/search?hl=en&q=dead+reckoning+robot&btnG=Google+Search&meta=). --Harry

# Specification #