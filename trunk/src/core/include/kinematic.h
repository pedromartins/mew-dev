/*
 * Defines the state classes used for steering.
 *
 * Part of the Artificial Intelligence for Games system.
 *
 * Copyright (c) Ian Millington 2003-2006. All Rights Reserved.
 *
 * This software is distributed under licence. Use of this software
 * implies agreement with all terms and conditions of the accompanying
 * software licence.
 */

/**
 * @file
 *
 * Holds the basic mathematical structures for the AI library.
 */
#ifndef MEW_CORE_KINEMATIC_H
#define MEW_CORE_KINEMATIC_H

#include "core.h"

namespace mew {
namespace core {

/*
 * This is messy, but it saves a function call or code duplication.
 */
#define EULER_INTEGRATION(duration, velocity, rotation) \
    position.x += (velocity).x*duration; \
    position.y += (velocity).y*duration; \
    orientation += (rotation)*duration; \
    orientation = real_mod_real(orientation, M_2PI);

/*
 * For this extended Kinematic datatype, it is capable of completing
 * Beeman integration. Error terms are ignored. NOTE: not done for orientation/rotations.
 */
#define BEEMAN_INTEGRATION(duration, position, velocity, newAcceleration, acceleration, oldAcceleration) \
	position.x += velocity.x*duration + (2*acceleration.x*duration*duration)/3 \
					- (oldAcceleration.x*duration*duration)/6; \
	position.y += veloctiy.y*duration + (2*acceleration.x*duration*duration)/3 \
					- (oldAcceleration.y*duration*duration)/6; \
	oldVelocity = velocity; \
	velocity.x += (newAcceleration.x*duration)/3 + (5*acceleration.x*duration)/6 \
					- (oldAcceleration.x*duration)/6; \
	velocity.y += (newAcceleration.y*duration)/3 + (5*acceleration.y*duration)/6 \
					- (oldAcceleration.y*duration)/6; \
	oldAccleration = accleration; \
	acceleration = newAcceleration

/**
 * SteeringOutput
 *
 * This is a movement requested by the steering system.
 *
 * It consists of linear and angular components. The components
 * may be interpreted as forces and torques when output from a
 * full dynamic steering behaviour, or as velocity and rotation
 * when output from a kinematic steering behaviour. In the former
 * case, neither force nor torque take account of mass, and so
 * should be thought of as linear and angular acceleration.
 *
 * In in use with our differential drive robot, the angular component
 * of SteeringOutputs are often neglected.
 */
class SteeringOutput
{
public:
	/**
	 * Creates a new steering action with zero linear and angular
	 * changes.
	 */
	SteeringOutput() : angular(0)
	{}

	/**
	 * Creates a new steering action with the given linear and
	 * angular changes.
	 *
	 * @param linear The initial linear change to give the
	 * SteeringOutput.
	 *
	 * @param angular The initial angular change to give the
	 * SteeringOutput.
	 */
	SteeringOutput(const Vector2df& linear, float angular = 0)
	: linear(linear), angular(angular)
	{}

	/**
	 * Zeros the linear and angular changes of this steering action.
	 */
	void clear()
	{
		linear.clear();
		angular = 0;
	}

	/**
	 * Checks that the given steering action is equal to this.
	 * SteeringOutputs are equal if their linear and angular
	 * changes are equal.
	 */
	bool operator == (const SteeringOutput& other) const
	{
		return linear == other.linear &&  angular == other.angular;
	}

	/**
	 * Checks that the given steering action is unequal to this.
	 * SteeringOutputs are unequal if either their linear or
	 * angular changes are unequal.
	 */
	bool operator != (const SteeringOutput& other) const
	{
		return linear != other.linear ||  angular != other.angular;
	}

	/**
	 * The linear component of the steering action, and the angular component.
	 * CAN be interpreted both as velocities, OR angular acceleration.
	 */
	Vector2df linear;
	float angular;
};

typedef SteeringOutput VelocityOutput;
typedef SteeringOutput AccelerationOutput;

/**
 * Represents the location of an object.
 *
 * A Static consists of a position and orientation. Position is
 * stored as a vector, rotation is a planar rotation about the y
 * axis.
 */
class Static {
public:

	/**
	 * Creates a new location with a 0 position and orientation.
	 */
	Static() : orientation(0.0f)
	{}

	/**
	 * Creates a location at the given position with no rotation.
	 */
	Static(const Vector2df& position)
	: position(position), orientation(0.0f)
	{}

	/**
	 * Creates a location with the given position and orientation.
	 */
	Static(const Vector2df& position, float orientation)
	: position(position), orientation(orientation)
	{}

	/**
	 * Creates a location with the position vector given as
	 * components and the given orientation.
	 */
	Static(float x, float y, float z, float orientation)
	: position(x, y, z), orientation(orientation)
	{}

	/**
	 * Assignment operator.
	 */
	Static& operator = (const Static& other)
	{
		position = other.position;
		orientation = other.orientation;
		return *this;
	}

	/**
	 * Zeros the position and orientation.
	 */
	void clear()
	{
		position.clear();
		orientation = 0.0f;
	}

	/**
	 * Checks that the given location is equal to this. Locations
	 * are equal if their positions and orientations are equal.
	 */
	bool operator == (const Static& other) const
	{
		return position == other.position &&
		orientation == other.orientation;
	}

	/**
	 * Checks that the given location is unequal to
	 * this. Locations are unequal if either their positions or
	 * orientations are unequal.
	 */
	bool operator != (const Static& other) const
	{
		return position != other.position ||
		orientation != other.orientation;
	}

	/**
	 * Perfoms a Euler integration onto this Static, given SteeringOutput.
	 * @param steer The velocity to apply over the integration.
	 *
	 * @param duration The number of simulation seconds to
	 * integrate over.
	 */
	void integrate(const SteeringOutput& steer, float duration);

	/**
	 * Sets the orientation of this location so it points along
	 * the given velocity vector.
	 */
	void setOrientationFromVelocity(const Vector2df& velocity);

	/**
	 * Returns a unit vector in the direction of the current
	 * orientation.
	 */
	Vector2df getOrientationAsVector() const;

	/**
	 * The position in 2D space cartesian coordinates from some designated origin.
	 *
	 * The orientation, as a Euler angle in radians around the positive x axis
	 * from the positive z axis.
	 */
	Vector2df position;
	float orientation;
};

/**
 * Represents the position and movement of an object.
 *
 * Kinematic extends location to add the first derivative of both
 * position and orientation: velocity and rotation. Rotation
 * consists of angular velocity about the positive z axis (the
 * first derivative of orientation in the Static structure), this
 * will be altered to be a full 3D angular velocity in due course.
 *
 * This version is MODIFIED by Hok Shun Poon, and provides more fields
 * for a higher-order kinematic class.
 * Past accelerations, rotations and velocities are accounted for, so that
 * Second-order integration techniques may be used.
 */
class Kinematic : public Static
{

	/**
	 * Creates a new Kinematic with zeroed data.
	 */
	Kinematic()
	: Static(), velocity(), rotation(0), acceleration(),
			oldVelocity(), oldRotation(0), oldAcceleration()
	{}

	/**
	 * Creates a new Kinematic with the given linear components
	 * and no rotation or orientation.
	 *
	 * @param position The position in space of the Kinematic.
	 * @param velocity The linear velocity of the Kinematic.
	 */
	Kinematic(const Vector2df& position, const Vector2df& velocity)
	: Static(position), velocity(velocity), rotation(0), acceleration(),
					oldVelocity(velocity), oldRotation(0), oldAcceleration()
	{}

	/**
	 * Creates a new Kinematic with the given location and linear
	 * velocity. The Kinematic has no rotation.
	 *
	 * @param loc The location of the Kinematic.
	 * @param velocity The linear velocity of the Kinematic.
	 */
	Kinematic(const Static& loc, const Vector2df& velocity)
	: Static(loc), velocity(velocity), rotation(0), acceleration(),
				oldVelocity(velocity), oldRotation(0), oldAcceleration()
	{}

	/**
	 * Creates a new Kinematic with the given location and no
	 * linear or rotational velocity.
	 *
	 * @param loc The location of the Kinematic.
	 */
	Kinematic(const Static& loc)
	: Static(loc), velocity(), rotation(0), acceleration(),
				oldVelocity(), oldRotation(0), oldAcceleration()
	{}

	/**
	 * Creates a new Kinematic with the given position,
	 * orientation, velocity and rotational velocity.
	 *
	 * @param position The position of the Kinematic.
	 * @param orientation The orientation of the Kinematic.
	 * @param velocity The linear velocity of the Kinematic.
	 * @param avel The angular velocity of the Kinematic.
	 */
	Kinematic(const Vector2df& position, float orientation,
			const Vector2df& velocity, float avel)
	: Static(position, orientation),
	velocity(velocity), rotation(avel), acceleration(),
	oldVelocity(velocity), oldRotation(avel), oldAcceleration()
	{}

	/**
	 * Zeros the location and velocity of this Kinematic.
	 */
	void clear()
	{
		Static::clear();
		velocity.clear();
		rotation = 0.0f;
		acceleration.clear();

		oldVelocity.clear();
		oldRotation = 0;
		oldAcceleration.clear();
	}

	/**
	 * Checks that the given Kinematic is equal to this.
	 * Kinematics are equal if their locations, velocities and
	 * rotations are equal.
	 */
	bool operator == (const Kinematic& other) const
	{
		return position == other.position &&
		orientation == other.orientation &&
		velocity == other.velocity &&
		rotation == other.rotation &&
		acceleration == other.acceleration &&
		oldVelocity == other.oldVelocity &&
		oldRotation == other.oldRotation &&
		oldAcceleration == other.oldAcceleration;
	}

	/**
	 * Checks that the given Kinematic is unequal to this.
	 * Kinematics are unequal if any of their locations,
	 * velocities or rotations are unequal.
	 */
	bool operator != (const Kinematic& other) const
	{
		return position != other.position ||
		orientation != other.orientation ||
		velocity != other.velocity ||
		rotation != other.rotation ||
		acceleration != other.acceleration ||
		oldVelocity != other.oldVelocity ||
		oldRotation != other.oldRotation ||
		oldAcceleration != other.oldAcceleration;
	}

	/**
	 * Sets the value of this Kinematic to the given location.
	 * The velocity components of the Kinematic are left
	 * unchanged.
	 *
	 * @param other The Static to set the Kinematic to.
	 */
	Kinematic& operator = (const Static& other)
	{
		orientation = other.orientation;
		position = other.position;
		return *this;
	}

	/**
	 * Copies (by assignment) all the attributes of the given
	 * Kinematic.
	 *
	 * @param other Reference to Kinematic to copy.
	 */
	Kinematic& operator = (const Kinematic& other)
	{
		orientation = other.orientation;
		position = other.position;
		velocity = other.velocity;
		rotation = other.rotation;
		acceleration = other.acceleration;
		oldVelocity = other.oldVelocity;
		oldRotation = other.oldRotation;
		oldAcceleration = other.oldAcceleration;
		return *this;
	}

	/**
	 * Modifies the value of this Kinematic by adding the given
	 * Kinematic.  Additions are performed by component.
	 */
	void operator += (const Kinematic&);

	/**
	 * Modifies the value of this Kinematic by subtracting the
	 * given Kinematic.  Subtractions are performed by component.
	 */
	void operator -= (const Kinematic&);

	/**
	 * Scales the Kinematic by the given value.  All components
	 * are scaled, including rotations and orientations, this is
	 * normally not what you want. To scale only the linear
	 * components, use the *= operator on the position and
	 * velocity components individually.
	 *
	 * @param f The scaling factor.
	 */
	void operator *= (float f);


	/**
	 * The following integration methods basically means "update this kinematic".
	 * The functionality of each version are as follows:
	 *
	 * - No acceleration or steering considered. Update Statics.
	 * - New acceleration must be considered. Update Statics, THEN Velocity and angular velocity.
	 * - Same with isotropic drag. (deleted)
	 * - Same with anisotropic drag. (deleted)
	 *
	 * This version will complete Beeman integration by interpreting the steering output as an acceleration.
	 */
	void integrate(float duration); // no change in acceleration now? hmmm!
	void integrate(const SteeringOutput& steer, float duration);


	/**
	 * Trims the speed of the kinematic
	 */
	void trimMaxSpeed(float speed);

	/**
	 * Sets the orientation of this location so it points along
	 * its own velocity vector.
	 */
	void setOrientationFromVelocity();

	/**
	 * The linear and angular velocities.
	 */
	Vector2df velocity;
	float rotation; // mainly unused.
	Vector2df acceleration;

	/**
	 * The former velocity and orientation values from the last time step.
	 */
	Vector2df oldVelocity;
	float oldRotation;
	Vector2df oldAcceleration;
};

} // END of namespace core
} // END of namespace mew

#endif // MEW_CORE_KINEMATIC_H
