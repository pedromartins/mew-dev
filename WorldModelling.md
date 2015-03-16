# Introduction #
In order to have the robot make informed decisions about movement, navigation and task-completion, it is necessary to keep a simple model of the map in memory, such that it is able to reason about its location, locations of other entities, and ultimately, how it should move to achieve specific goals.

# Grid #
The world can very simply be modelled as a 2D grid.
The resolution of the grid squares can be adjusted by a variable parameter, for testing purposes. Grid squares can be as small as 1cm^2 if required.

The grid can be simply implemented as a 2D-array integer array in C. The integer can hold information about the properties of that particular grid square. Properties may include:
  * Elevation
  * Passibility
  * Proximity to known obstructions.

Viewing with the starting zones at the bottom, the origin square (0,0) of the grid should be at the lower-left corner, with the _x_ coordinate extending towards the right, and the _y_ coordinate extending up.


# Features #
Map features are objects of interest, which may or may not affect grid square properties.

|`Wall` | Walls of the map |
|:------|:-----------------|
|`FlatBuildingZone`|Type 1 building zone|
|`ElevatedBuildingZone`|Type 2 building zone at the edge |
|`CircularBuildingZone`|Type 3 building zone at the middle of the map |
|`Cylinder`|Basic playing element|
|`Lintel` |Basic playing element|