# Introduction #
How does the robot move from point A to point B?
Knowing that the current robot's position is in A, and also knowing where B is relative to that, is it really sufficient to say "Turn x degrees, turn on motor for 8 seconds, turn off motor"?
The chances are, no, not at all.
Firstly, hard-coding a path is seriously not a good idea. We're not even using any sort of feedback to check whether the steps coded have been executed correctly. What if a slight bump on the playing field caused the robot to change orientation unexpectedly?
What if some unexpected obstacle (i.e., the opponent robot) steered into our original path and obstructs our robot?

Steering is the 2nd to bottom lowest-level problem to be solved, sitting above the [DriveSystem](DriveSystem.md), and immediately below [Pathfinding](Pathfinding.md). Steering, in our case, typically ensures that the entity in question (our robot) always makes a **decent effort** at moving towards its goal position/orientation in a constructive way, without being compromised by obstructions. The goal position/orientations are typically provided by pathfinding. Of course, there are cases where steering proves to be completely impossible, in which case, `pathfinding` is notified and a plan is re-calculated.

The Steering layer is analogous to the job of the arms and legs of the driver of a car: the driver receives input from his/her eyes (frontal, back, internal/side mirror views), and from his/her ears- planning and mapping occurs within the brain (like decision making and path-finding), and then an appropriate movement of the steering-wheel is made by his/her arms to command the car to steer left or right, simultaneously with appropriate movements of the gas and brake pedals.
Of course, the actual mechanics behind how a car actually moves, and how it turns, and how much it turns by, is totally oblivious to the driver (AND his arms and legs!!!); all of that is handled by the `drivesystem`.

In the simplest sense. This layer translates goals to commands.

# Approach #
I propose that we use a behaviour-oriented approach to steering control.
Given goals, behaviours are algorithms which positively influence the decision to execute a particular command, which generally, after execution, should cause the entity to make progress towards its goal. A driver, who wishes to get to the local Post Office 100 metres down the road, would have the 'Seek' behaviour running on the goal 'Post Office', which would influence the driver to execute the 'Accelerate' command, such that the car moves closer towards the Post Office; the goal.

Of course, this is a horrifically simplified view of the problem. Suppose at 50 metres to go, there was road-works lined with traffic cones on your side of the road. What do you do? You avoid them, of course!
'Avoidance' of obstructions is yet another behaviour, which might run on the goal 'traffic cones', which would influence the driver to execute the 'Turn away from point' command, and 'brake' etc. to ensure no collisions occur between the cones and car (even, stopping!).

However, when 'Avoidance' is running, it doesn't mean that the driver forgets what he was doing completely, and attempts to u-turn to get as far from the cones as possible (I mean, that IS what avoidance is, right?): that would be a bit counter-intuitive. He/she still wants to get to the post-office; it's only cones!

Therefore, the blending of both behaviours are needed.
We'll discuss how to implement Behaviours, and go through several typical behaviours, and discuss different ways to blend them together, so that the final commands executed (the steering output) is constructive towards the making progress towards the goal.


# Concepts #
Below are concepts that will build up to ultimately understanding the steering algorithms that will be employed. Notice that we assume that the robot is able to reliably produce good estimates of its own location and orientation, throughout the next section.

I'm going to go through some essential data structures, which we shall be manipulating later on.


## Static ##
'Static' refers to two properties of any entity travelling at constant velocity (which, do not forget, may mean it is stationary):

  * Absolute Cartesian coordinates (aka. position, in the form (x,y), where x and y are both real numbers)
  * Orientation (the way that the object is facing. N.B! This is not necessarily the way that the object is travelling!! There is no bearing between the way something faces and the direction it travels in; that is determined by the velocity, later on)

This can be represented by the C++ struct:
```
struct Static {
  Point2df position;
  float orientation; // goes from 0 to 2*pi; describes angle offset clockwise from some preset 0-bearing. Could be interpreted as a unit vector (Vector2df) using orientationAsVector();
};
```

While this keeps position and orientation data, other physical properties have been severely neglected: why assume that we must work with a constant velocity? We'll extend this struct a little further to make it more useful.

## Kinematic ##
While statics is a very simple model of representing the state of entities in relation to the world, there's no real information regarding whether some entity is currently moving or not. Storing information about a current entity's velocity, and also the entity's current rotational speed gives us the new `Kinematic` struct/class.

```
struct Kinematic {
  Vector2df position;
  float orientation;
  Vector2df velocity;
  float rotation;
};
```

## Steering Outputs ##
Ignoring that our robot has two wheels (a separate problem altogether), we must now introduce the `SteeringOutput` struct. Instances of this struct are returned by a steering algorithm to instruct the entity how it should change its current velocity (so that, say, it could be controlled to go to a certain point on the map.) Steering outputs is a pair of

  * linearAcceleration - The linear acceleration that should be applied towards any direction.
  * angularAcceleration - The angular acceleration that should be applied towards any direction.

# Details #