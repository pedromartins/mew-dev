/*
 * actuator.h
 *
 *  Created on: 01-Apr-2009
 *      Author: fushunpoon
 */

#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include <core/core.h>


enum TurnDirection {
	LEFT = -1,// -1
	STRAIGHT, // 0
	RIGHT     // 1
};

/**
 * Represents a motor, but what should an IMotor actually provide, in
 * terms of functoinality?
 */
class IMotor {
	/// TODO!!!!

};

/**
 * A SimpleDrive may be instructed to move a robot forward a
 * certain distance x, may turn at *90 degrees* (and 180, at times).
 *
 * The action of turning or moving forward cannot be pre-empted.
 *
 * To achieve the maneovre accurately, the SimpleDrive is allowed
 * to poll any devices it feels necessary.
 */
class ISimpleDriveSystem {
public:
	virtual ~ISimpleDriveSystem() {}

	/**
	 * Moves the robot forward at some* speed (we do not know what speed).
	 * Pre: None.
	 * Post: The robot will have been moved squares*x cm away from
	 * the point at which the method was called.
	 * @param squares
	 */
	virtual void moveForward(int squares) = 0;

	/**
	 * Pre: None.
	 * Post: The robot will have turned 90 degrees in the direction specified.
	 * @param dir
	 */
	virtual void turn(TurnDirection dir) = 0;
};

/**
 * An actual (physical) implementation of the SimpleDriveSystem
 * specificaiton.
 */
class SimpleDifferentialDrive : public ISimpleDriveSystem {
public:
	/// TODO

	/**
	 * Moves the robot forward at some* speed (we do not know what speed).
	 * Pre: None.
	 * Post: The robot will have been moved squares*x cm away from
	 * the point at which the method was called.
	 * @param squares
	 */
	virtual void moveForward(int squares);

	/**
	 * Pre: None.
	 * Post: The robot will have turned 90 degrees in the direction specified.
	 * @param dir
	 */
	virtual void turn(TurnDirection dir);
private:
	IMotor *left;
	IMotor *right;

	float axle_length;  // the distance between the two wheels.
	float radius;		// wheel radius in mm.
};

/**
 * A SimpleClaw may be instructed to open or close. Whether the
 * claw actually grabbed anything is not of concern.
 */
class ISimpleClaw {
public:
	virtual ~ISimpleClaw() {}

	/**
	 * Closes the claw, if it isn't already closed.
	 */
	virtual void close() = 0;

	/**
	 * Opens the claw, if it isn't already opened.
	 */
	virtual void open() = 0;
private:

};

/**
 * A DriveSystem
 * the drive system should actuate underlying devices to attempt to MATCH the
 * acceleration given.
 *
 * If accelerations are too great for the Drive system, then the actual
 * output acceleration will have a truncated magnitude.
 *
 * By repeatedly calling update (as often as possible), the drive system should
 * match the acceleration.
 */
class IDriveSystem {
public:
	virtual ~IDriveSystem() {}

	virtual Vector2df getAcceleration() = 0;
	virtual void setAcceleration(const Vector2df& acceleration) = 0;

	// continue to match acceleration.
	virtual void update() = 0;
};

/**
 * DifferentialDriveSystem
 *
 * Given references to two motors, and knowing the wheel radius, and also the distance between the dimension
 * Controls the movement of the two wheels of the robot, such that the acceleration outputs would eventually
 * match that of the given target (directed) acceleration.
 *
 * The differential drive system doubles up as 2 odometric
 * meters:
 *  -
 * Has direct reference to the Kinematic
 */
class DifferentialDrive : public IDriveSystem {
public:

	DifferentialDrive(IMotor *left, IMotor *right, float axle_length, float wheel_radius_mm);
	virtual ~DifferentialDrive() {}

	virtual Vector2df getAcceleration() { return desired_acceleration; }
	virtual void setAcceleration(const Vector2df& acceleration) {
		desired_acceleration = acceleration; // update the acceleration and update.
		update();
	}

	/* Updates the driving system to alter accelerations,
	 * correcting the drive system's course.
	 * Assumes current kinematic most updated. */
	virtual void update();

protected:

private:
	IMotor *left;		// reference to the left motor
	IMotor *right;		// reference to the right motor
	float axle_length;  // the distance between the two wheels.
	float radius;		// wheel radius in mm.

	Vector2df desired_acceleration;

	Kinematic *kinematic; // The kinematic which the controller should update?!
};




#endif /* ACTUATORS_H_ */
