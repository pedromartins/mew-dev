#ifndef KINEMATIC_H_
#define KINEMATIC_H_

#include "steeringoutput.h"


/**
 * Represents the position and movement of a character or other object.
 *
 * Kinematic<T,O> extends static to add the first derivative of both
 * position and orientation: velocity and rotation. Rotation
 * consists of angular velocity about the positive z axis (the
 * first derivative of orientation in the Static<T,O> structure), this
 * will be altered to be a full 3D angular velocity in due course.
 */
template<typename T,typename O>
struct Kinematic<T,O> : public Static<T,O>
{
	/**
	 * The linear velocity.
	 */
	Vector2d<T> velocity;

	/**
	 * The angular velocity.
	 */
	O rotation;

	/**
	 * Creates a new Kinematic<T,O> with zeroed data.
	 */
	Kinematic()
	: Static<T,O>(), velocity(), rotation(0)
	{}

	/**
	 * Creates a new Kinematic<T,O> with the given linear components
	 * and no rotation or orientation.
	 *
	 * @param position The position in space of the Kinematic<T,O>.
	 * @param velocity The linear velocity of the Kinematic<T,O>.
	 */
	Kinematic(const Vector2d<T>& position, const Vector2d<T>& velocity)
	: Static<T,O>(position), velocity(velocity), rotation(0)
	{}

	/**
	 * Creates a new Kinematic<T,O> with the given static and linear
	 * velocity. The Kinematic<T,O> has no rotation.
	 *
	 * @param loc The static of the Kinematic<T,O>.
	 * @param velocity The linear velocity of the Kinematic<T,O>.
	 */
	Kinematic(const Static<T,O>& loc, const Vector2d<T>& velocity)
	: Static<T,O>(loc), velocity(velocity), rotation(0)
	{}

	/**
	 * Creates a new Kinematic<T,O> with the given static and no
	 * linear or rotational velocity.
	 *
	 * @param loc The static of the Kinematic<T,O>.
	 */
	Kinematic(const Static<T,O>& loc)
	: Static<T,O>(loc), velocity(), rotation(0)
	{}

	/**
	 * Creates a new Kinematic<T,O> with the given position,
	 * orientation, velocity and rotational velocity.
	 *
	 * @param position The position of the Kinematic<T,O>.
	 * @param orientation The orientation of the Kinematic<T,O>.
	 * @param velocity The linear velocity of the Kinematic<T,O>.
	 * @param avel The angular velocity of the Kinematic<T,O>.
	 */
	Kinematic<T,O>(const Vector2d<T>& position, double orientation,
			const Vector2d<T>& velocity, double avel)
	: Static<T,O>(position, orientation),
	velocity(velocity), rotation(avel)
	{}

	/**
	 * Zeros the static and velocity of this Kinematic<T,O>.
	 */
	void clear()
	{
		Static<T,O>::clear();
		velocity.clear();
		rotation = 0.0f;
	}

	/**
	 * Checks that the given Kinematic<T,O> is equal to this.
	 * Kinematics are equal if their statics, velocities and
	 * rotations are equal.
	 */
	bool operator == (const Kinematic<T,O>& other) const
	{
		return position == other.position &&
		orientation == other.orientation &&
		velocity == other.velocity &&
		rotation == other.rotation;
	}

	/**
	 * Checks that the given Kinematic<T,O> is unequal to this.
	 * Kinematics are unequal if any of their statics,
	 * velocities or rotations are unequal.
	 */
	bool operator != (const Kinematic<T,O>& other) const
	{
		return position != other.position ||
		orientation != other.orientation ||
		velocity != other.velocity ||
		rotation != other.rotation;
	}

	/**
	 * Checks that the given Kinematic<T,O> is less than this.  A
	 * Kinematic<T,O> is less than another Kinematic<T,O> if its position
	 * along the x-axis is less than that of the other Kinematic<T,O>.
	 */
	bool operator < (const Kinematic<T,O>& other) const
	{
		return position.x < other.position.x;
	}

	/**
	 * Sets the value of this Kinematic<T,O> to the given static.
	 * The velocity components of the Kinematic<T,O> are left
	 * unchanged.
	 *
	 * @param other The Static<T,O> to set the Kinematic<T,O> to.
	 */
	Kinematic<T,O>& operator = (const Static<T,O>& other)
	{
		orientation = other.orientation;
		position = other.position;
		return *this;
	}

	/**
	 * Copies (by assignment) all the attributes of the given
	 * Kinematic<T,O>.
	 *
	 * @param other Reference to Kinematic<T,O> to copy.
	 */
	Kinematic<T,O>& operator = (const Kinematic<T,O>& other)
	{
		orientation = other.orientation;
		position = other.position;
		velocity = other.velocity;
		rotation = other.rotation;
		return *this;
	}

	/**
	 * Modifies the value of this Kinematic<T,O> by adding the given
	 * Kinematic<T,O>.  Additions are performed by component.
	 */
	void operator += (const Kinematic<T,O>&);

	/**
	 * Modifies the value of this Kinematic<T,O> by subtracting the
	 * given Kinematic<T,O>.  Subtractions are performed by component.
	 */
	void operator -= (const Kinematic<T,O>&);

	/**
	 * Scales the Kinematic<T,O> by the given value.  All components
	 * are scaled, including rotations and orientations, this is
	 * normally not what you want. To scale only the linear
	 * components, use the *= operator on the position and
	 * velocity components individually.
	 *
	 * @param f The scaling factor.
	 */
	void operator *= (double f);

	/**
	 * Performs a forward Euler integration of the Kinematic<T,O> for
	 * the given duration.  This applies the Kinematic<T,O>'s velocity
	 * and rotation to its position and orientation.
	 *
	 * \note All of the integrate methods in this class are
	 * designed to provide a simple mechanism for updating
	 * position. They are not a substitute for a full physics
	 * engine that can correctly resolve collisions and
	 * constraints.
	 *
	 * @param duration The number of simulation seconds to
	 * integrate over.
	 */
	void integrate(double duration);

	/**
	 * Perfoms a forward Euler integration of the Kinematic<T,O> for
	 * the given duration, applying the given acceleration.
	 * Because the integration is Euler, all the acceleration is
	 * applied to the velocity at the end of the time step.
	 *
	 * \note All of the integrate methods in this class are designed
	 * to provide a simple mechanism for updating position. They are
	 * not a substitute for a full physics engine that can correctly
	 * resolve collisions and constraints.
	 *
	 * @param steer The acceleration to apply over the
	 * integration.  @param duration The number of simulation
	 * seconds to integrate over.
	 */
	void integrate(const SteeringOutput& steer, double duration);

	/**
	 * Perfoms a forward Euler integration of the Kinematic<T,O> for the given
	 * duration, applying the given acceleration and drag.
	 * Because the integration is Euler, all the acceleration is applied to
	 * the velocity at the end of the time step.
	 *
	 * \note All of the integrate methods in this class are designed
	 * to provide a simple mechanism for updating position. They are
	 * not a substitute for a full physics engine that can correctly
	 * resolve collisions and constraints.
	 *
	 * @param steer The acceleration to apply over the integration.
	 *
	 * @param drag The anisotropic drag to apply. The force
	 * component of the SteeringOutput is interpreted as linear drag
	 * coefficients in each direction, and torque component is
	 * interpreted as the rotational drag.
	 *
	 * @param duration The number of simulation seconds to
	 * integrate over.
	 */
	void integrate(const SteeringOutput& steer,
			const SteeringOutput& drag,
			double duration);

	/**
	 * Trims the speed of the Kinematic<T,O> to be no more than that
	 * given.
	 */
	void trimMaxSpeed(double speed);

	/**
	 * Sets the orientation of this static so it points along
	 * its own velocity vector.
	 */
	void setOrientationFromVelocity();
};

#endif
