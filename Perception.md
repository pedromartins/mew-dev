# Introduction #
The robot must be able to travel around the playing field autonomously, without running into obstacles, and completing a task without any help whatsoever. To achieve this, the robot must have a WorldModel of the world around it, such that it could work and reason with it, to ensure any decisions made to move the robot are informed and will ensure the robot's output behaviour is sensible.

Thankfully, this model needn't be built from scratch; this is due to the fact that the playing field is already well defined, which, given that we encode all the information given in the specification into some representation the robot could work with, this is a very good model already.

However, that information may not be totally reliable. The locations of cylinders and the location of the opponent robot is totally unpredictable. Cylinders may have been moved by the opponent robot into the path of ours. Our robot must then update the model of the world.


The way the model is represented, and subsequently updated via information from sensors is the job of the perception system. How reliable are our sensors? What does a raw sensor reading mean in the context of our perception of the world? How should we interpret this data to reflect changes in the world in our world model?