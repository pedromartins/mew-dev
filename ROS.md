# Introduction #
[ROS](http://www.ros.org/wiki/) is a robotics development environment and framework that provides many bindings to useful tools, packaging facilities, and a lot of other goodies.
Contrary to what its name may suggest, ROS is not really an operating system, but its various shell-scripts integrate well into the UNIX or UNIX-like environments well via the shell commands and daemons such that it appears to become a part of your opearting system.

# Installation #
To install ROS, follow the instructions on http://www.ros.org/wiki/ROS/Installation.

## Troubleshooting ##
If you get compilation errors about some uint\_8 type not being declared, then add the following line in the #include section of the source code file in question and recompile:
```
#include <stdint.h>
```

## Fixing rxgraph ##
If you're experiencing problems when running rxgraph on [6](tutorial.md) and running into strange exceptions:
```
Type error: font_options must be of type cairo.FontOptions or None
```
then download the lastest xdot script (used to render nice diagrammatic things) [here](http://jrfonseca.googlecode.com/svn/trunk/xdot/xdot.py) and replace the ROS one.
This will cause a few incompatibilities with ros/tools/rosgraph/src/rosgraph/rxgraph.py, so let's fix those:

Remove the second parameter of the init call (the numbers may vary)
```
rosgraph.xdot.DotWindow.__init__(self, (1024, 768))
```
so that it looks like
```
rosgraph.xdot.DotWindow.__init__(self)
```
and then comment out the line
```
self.widget.set_on_rotate(self.on_rotate)
```
so that it looks like
```
# self.widget.set_on_rotate(self.on_rotate)
```

# Development with ROS #
The great thing about ROS is that all the code we have written can be carefully
## Porting existing C/C++ code ##
The code that we have written is C/C++ based, and for our sensors, they fit snuggly  into the ROS model of modular design as a 'publisher'.
In the tutorials
http://www.ros.org/wiki/ROS/Tutorials/WritingPublisherSubscriber%28c%2B%2B%29