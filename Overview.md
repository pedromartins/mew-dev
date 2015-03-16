# Introduction #
Building software for a robot means that we have not only got to code, but actually engineer our code.
I present here a way of breaking up our problem into smaller sub-problems, such that developers know what part of the project you're working on, and how, on the grander scale, everything will collaborate together and work in harmony to produced desired output.

# The Diagram #
![http://mew-dev.googlecode.com/svn/wiki/images/Robotsoftwarediagram.svg](http://mew-dev.googlecode.com/svn/wiki/images/Robotsoftwarediagram.svg)


# Technologies Employed #
To manage this project, I wish to highlight which technologies have been used in what parts of the project.

## Programming langages ##
  * C - used in the `electronicsinterface`. This is closer to what the electronics team actually uses for programming on their Arduino. They have no use for Object Oriented Programming.
  * C++ - used in [controlsystem](controlsystem.md) and [perceptionsystem](perceptionsystem.md), because both of these must run very fast, and be able to intercommunicate quickly. This is best done via the use of C++ references/pointers.
  * SWI-Prolog - used in the [decisionsystem](decisionsystem.md). Provides a sturdy inference engine with which we could declaratively state the problem at hand, and let Prolog's resolution strategy (depth-first search with backtracking, optionally with depth limit) to solve our most complicated of decision problems. SWI will call functions exposed by the `controlsystem`, and will wait patiently until the controlsystem reports success or failure of achieving that goal.

## Tools ##
  * gcc/g++ (The GNU Compiler Collection for C/C++) - this should be our main compiler for C/C++ code, because we shall be operating under a UNIX environment on the robot. Development could be done on whichever platform you choose; just ensure that the source-code compiles under UNIX, and we're good =]
  * 'makes' (builds the project)
  * [CMake](GettingStarted.md) - We're using CMake to manage the build of our project. CMake makes makefiles for GNU make, which actually calls the appropriate tools for compilation of the entire project. It's a really simple build system to use, and I hope that keep things nice and tidy for us, as opposed to getting in our way.
  * plld - SWI-Prolog linker for producing libraries that expose functionality implemented in C++. I.e. this is a part of SWI-Prolog's Foreign Function Interface for C/C++ functions.