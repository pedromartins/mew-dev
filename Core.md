# Introduction #
Common classes, data structures and algorithms used in the project.

`#include <core/core.h>`

# Details #

Add your content here.  Format your content with:
  * `Vector2d<T>`
    * `Vector2dd` Double precision
    * `Vector2df` Single precision
    * `Vector2di` Integer

This provides a templated vector class. Provides a pair of the specified type. Its elements are known as _x_ and _y_ for obvious reasons.

  * `AStarSearch<SearchNode>` A templated A`*` implementation. You must provide a SearchNode type that supports several functions, such as `GetChildren()` and `IsGoal()` and similar things. Consult the example test program.