/*
 * actuator.h
 *
 * Contains definitions for drive systems, temple assemblers and high-level
 * abstract devices.
 *
 *  Created on: 15-Feb-2009
 *      Author: Hok Shun Poon
 */

#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include <core.h>

using namespace mew::core;

/**
 * IDriveSystem
 *
 * The job of the drive system is that given a particular acceleration,
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
	virtual ~IDriveSystem();

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
class DifferentialDriveSystem : public IDriveSystem, IVelocimeter, IAngularVelocimeter {
public:

	DifferentialDriveSystem(IMotor *left, IMotor *right, float axle_length, float wheel_radius_mm);
	virtual ~DifferentialDriveSystem();

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

/**
 * IMotor
 *
 * Represents a motor with or without an encoder.
 */
class IMotor {
	virtual ~IMotor();
	virtual bool hasEncoder();
	virtual float getRPM();
	virtual void setRPM(float rpm);
};

/**
 * IServo
 *
 * Represents a servomotor.
 */
class IServo {
	virtual ~IServo();
	virtual float getAngle();
	virtual void setAngle();
};

/**
 * TempleBuildingClaw
 *
 * Represents the temple building claw.
 * TODO : is this necessary?
 */
 class TempleBuildingClaw {
 	virtual ~TempleBuildingClaw();


 };


#endif /* ACTUATOR_H_ */
