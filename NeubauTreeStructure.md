**Neubau** is the mew-dev team's current source-tree. It contains all the source-code that is required to build robot-control software.

## Principles ##
The main principles of the Neubau project is this:

  * always-working build. ALWAYS. SERIOUSLY, DON'T BREAK THE BUILD!!!
    * no dirty commits unless absolutely necessary
  * simple build system using CMake
  * 1-2 line configuration files (CMakeLists.txt)
  * no Makefiles, ever.
  * out-of-source build, separating binaries from source-code
  * regression tested code to ensure libraries and units work as intended.
  * NO include directories


## Migrating from the Old Tree ##
If you've always been using `trunk`, then good news!!! To use Neubau, all you have to do is check it out into a completely separate location. See GettingStarted.
Things are **seriously** simple now, **seriously**.

One particular explanation is required, and that is the "Dirty commit".
A "**dirty commit**" is a commit that [breaks the build](BrokenBuild.md). The build is considered broken when:
  * cmake doesn't complete properly
  * make returns an error or severe warnings

Failing tests are acceptable, because failed tests imply further work is required on the source code to correct it.

## SOURCE TREE STRUCTURE!!! (by Pedro, originally!) ##
```
 /            The Project's source code ROOT. In CMake, this is
 |            ${NEUBAU_SOURCE_DIR}. The name of the root is determined by the
 |            developer when the source tree is checked out from SVN.
 |
build/        This is the default build directory. In CMake,
 |            this is ${NEUBAU_BINARY_DIR}. 
 |
control/      The controlsystem abstracts away the details of actuation, to
 |            present a simpler interface geared towards solving problems.
 |            Decomposes tasks into calls to devices.
 |
 |- movement/ Deals with movement goals
 |- robot/	  State that is needed for the logic.
 |
core/		  Core contains abstract general purpose things.
 |
decision/     The decision system is responsible for the higher level
 |            reasoning to plan the sequence of actions that is to be taken.
 |
device/       (Also: driver layer) Uses electronic or simulated layer calls
 |            to provide a higher level interface for the sensors and actuators.
 |            (e.g will contain calls like goForward(2 metres) ).
 |            Will have the low-level logic for controlling the actuators.
 |
electronics/  Implementations of low-level physical device communications protocols.
 |            Uses basic serial communications interfaces to provide a meaningful
 |            interface to users of the hardware devices.
 |
experimental/ Experimental features that need to be tested individually to ensure
 |            their full functionality before integrating it with the larger system.
 |
 |- virtual/  Provides totally virtualized device, electronic and hardware layers.
 |            These are essentially mock-up classes to ensure this architecture
 |            works.
 |            Gives us the so called 'simulated world' layer that may entirely
 |            replace the 'electronic' layer if need be. Abstract devices should
 |            still work.
 |
perception/   Keeps an internal model of the external world and a robot state.
 |            Provides a logic unit that uses information extracted from perceptive
 |            devices (such as sensors and actuator feedback) to update the stored
 |            states. This will happen periodically or upon request, so that
 |            higher logic (control and making decisions [goal generation])
 |            may make the best decisions.  
 |
test/         Keeps test source code for unit tests for each of the layers.
 |- control   The directory structure of test will mimick that of the top-level
 |- core      main direcories, so that tests could be put into their respective
 |- decision  and corresponding directories.
 |- .
 |- .
 |- .
```