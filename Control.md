# Introduction #
The `controlsystem` abstracts away the details of actuation, to present a simpler interface geared towards solving problems.


# The Design #
To implement the hybrid approach, the software team requests that **most actuators have a feedback mechanism** or querying interface, with which reasoning can be done with values retrieved.

There are two extremes of implementing the hybrid control system:
Two tier, or hierarchical.

## Two-tier design ##
  * First tier
    * Localizing
    * Decision
    * Planning
    * Keeping an updated model
  * Bottom tier
    * Driving
    * Other actuation
    * Sensory

## Fully hierarchical ##
The control system is one rather complicated tree. Each of the nodes represent a well-defined behaviour. Sub-nodes also represent a smaller and simpler behaviour. Higher  behaviours blend, or otherwise combine sub-behaviours appropriately to achieve its goal, whereas sub-behaviours in turn may utilize yet simpler behaviour to achieve its goals.

Typically, commands are delegated down the hierarchy (e.g. actuation), while sensor readings, state data, and other feedback propagate up the hierarchy for handling at various levels. Tasks are typically given more computing time on the higher level, such as mapping, planning and decision-making. Lower levels require relatively less computing power of the hierarchy execute much faster- tasks such as polling sensors, or actuating.

**In our control system, we will be building a two- or three-tier architecture. In the design, it isn't clear how many 'tiers' there are, but it's important to recognise that layers do exist, and lower layers should be oblivious to the workings of higher layers.**


## Details ##
  * `Robot` - Maintains a reference to current `RobotState`. Provides functions to update the best estimate of the `RobotState`. Maintains references to `IAngularVelocimeter`s, `ISpedometer`s, `ILocator`s, and `IOrientator`s and applies an algorithm to data gathered from each of these sensors (such as calculating the mean) to update the RobotState.
  * `IAngularVelocimeter` - Returns a float of how much the robot is turning at this moment in time. Measured in _degrees per second_, +ve values are clockwise, -ve values are anti-clockwise.
  * `IOrientator` - Returns a float of the 'absolute' orientation of the robot (relative to the playing area's orientation). Achieved via using devices such as a compass.
  * `ILocator`- Returns a Point2df of the 'absolute' location of the robot (relative to an arbitrary origin set on the plane of the playing area's ground).
  * `ISpedometer` - Returns a float of the speed at which the robot is travelling. Derivable from the drive system, assuming stepper motors or rotary encoders are used.
  * `IServoController` - Control subsystem for servo(motor)s only, to perform intelligent coordinated tasks, e.g. robotic arm with 3 degrees of freedom: provide simple interface via Inverse Kinematics. Implementation of this interface is totally dependent on the physical configuration of the servos, and how they are used. **`TempleBuildingServoController` will be extended when implementation details become more clear.**
  * `IDriveSystem` - Control subsystem for locomotion only, to perform implementation specific control of motors, e.g. Differential drives use motors to steer differently from Skid-steering. **`DifferentialDriveSystem` will be extended when implementation details becomes more clear**.
  * `IProgramLogic` - Represents a program that the robot should run. This software, therefore, could be re-configured to **`TempleBuildingLogic` will be extended when `DifferentialDriveSystem` and `TempleBuildingServoController` are well defined.**
  * `OdometricLocator` and `OdometricOrientator` - Odometric methods are used to provide an estimate of the location and orientation through these classes respectively. Odometric methods refer to the use of an initial `RobotState` in conjunction with `RobotState`s at later points in time to derive the position and orientation of the robot. These methods are prone to error, but however, does provide a very good estimate of the relative location, given that the initial state was accurate.


MAJOR REVISIONS REQUIRED!