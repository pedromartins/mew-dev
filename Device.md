# Introduction #
The device layer provides hardware abstraction over the various components that we will be using in our project, such that our algorithms can be oblivious to implementation. This ensures that control, planning, and other pieces of pure software code we write will be portable in the future, and modularizing code to make it more readable.

This works in much the same way as commerical operating systems which have their own Hardware Abstraction Layer (HAL), for abstracting the functionality of a printer, or hard-drive, or what-have-you.


## The Devices ##

Currently defined abstract devices are:
  * `IMotor` An object whose power level can be changed, such that its rotational velocity is proportional.
  * `Sensor` A particular object that gives a single integer value which is known as a 'reading'.

Currently implementing devices are:
  * `I2CMotor` A motor which is controlled via an I2C interface.

In addition to this, we have:
  * `Arduino` class