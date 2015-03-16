Welcome to the Software Team subwiki.

Looks complicated, right? Hah well, don't despair. The pages put on this wiki are here more as a road-map and a general map so that we know 'where' we are, and what part of the software the code you write fit into.

I do recommend reading the GettingStarted page if you're completely lost.


You may see some references to the "Old Tree" - well, that refers to `svn/trunk`. However, that tree is rather dirty and outdated.
A new tree by the name of "Neubau" (`svn/neubau`) was created so that everything **working** can be put in there. The principles underlying the being of this tree can be found in SourceTreeStructure, which every developer should adhere to and respect.

  * [Overview](Overview.md) A description of how the project is layed out, and where resources can be found
  * [Getting Started!](GettingStarted.md) Useful information to get started with development here
  * [How to use SVN](SVNHowTo.md) Describes how to use Subversion to check out code

  * [The Neubau Tree Structure](NeubauTreeStructure.md) A description of the new source tree
  * [Coding conventions](CodingConventions.md) What code should look like

  * [Decision](Decision.md) Generates high-level goals by searching problem space. No planning :/
  * [Control](Control.md) Controls the robot's actuators with given information to achieve or finitely fail at achieving goals. Lower-level planning is done here.
    * [Movement](Movement.md) Movement algorithms are used here.
      * [SteeringBehaviours](SteeringBehaviours.md) Advanced (and not necessarily practical) approach to movement
        * [BehaviourArbitration](BehaviourArbitration.md) Combines outputs of steering behaviours to produce a final output
    * [Build](Build.md) Control algorithms for the claw (currently). Very simplistic.
  * [Perception](Perception.md) The robot's interpretation of the world and itself. Keeps robot and world state, and processes incoming data from sensors to provide
    * [Modelling the world](WorldModelling.md) Representation of the world and problem space.
    * [Localization](Localization.md)
      * [Odometric](Odometric.md) Dead reckoning techniques with limited information about change of distance from initial position
  * [Device](Device.md) The virtualized device layer (or drivers layer) provides hardware abstraction
    * [Actuator](Actuator.md)
      * [DriveSystem](DriveSystem.md)
      * [Claw](Claw.md)
    * [Sensory](Sensory.md)
      * [ComputerVision](ComputerVision.md)
      * [IRSensors](IRSensors.md)
      * [UltrasoundSensors](UltrasoundSensors.md)
  * [Electronic](Electronic.md) The electronic layer deals with low-level communication with hardware
  * [Core](Core.md) Common classes, useful data structures and generalized algorithms used throughout the project are housed in core
  * [Virtual](Virtual.md) A virtual replacement of the real world and hardware, to provide a simple testing platform. Interfacing with robot frameworks and simulators can be done here.

  * [Links and resources](SoftwareTeamResources.md) Miscellaneous links and resources that may be of interest