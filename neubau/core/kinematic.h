#ifndef KINEMATIC_H_
#define KINEMATIC_H_

#include "static.h"

/**
 * Represents the position and movement of a character or other object.
 *
 * Kinematic extends static to add the first derivative of both
 * position and orientation: velocity and rotation. Rotation
 * consists of angular velocity about the positive z axis (the
 * first derivative of orientation in the Staticff structure), this
 * will be altered to be a full 3D angular velocity in due course.
 *
 * Kinematic will use single floating point precision for both
 * position and rotation.
 */
typedef Static<float,float> Staticff;

struct Kinematic : public Staticff
{
	/**
	 * The linear velocity.
	 */
	Vector2df velocity;

	/**
	 * The angular velocity.
	 */
	float rotation;

	/**
	 * Creates a new Kinematic with zeroed data.
	 */
	Kinematic()
	: Staticff(0,0), velocity(), rotation(0)
	{}

	/**
	 * Creates a new Kinematic with the given linear components
	 * and no rotation or orientation.
	 *
	 * @param position The position in space of the Kinematic.
	 * @param velocity The linear velocity of the Kinematic.
	 */
	Kinematic(const Vector2df& position, const Vector2df& velocity)
	: Staticff(position), velocity(velocity), rotation(0)
	{}

	/**
	 * Creates a new Kinematic with the given static and linear
	 * velocity. The Kinematic has no rotation.
	 *
	 * @param loc The static of the Kinematic.
	 * @param velocity The linear velocity of the Kinematic.
	 */
	Kinematic(const Staticff& loc, const Vector2df& velocity)
	: Staticff(loc), velocity(velocity), rotation(0)
	{}

	/**
	 * Creates a new Kinematic with the given static and no
	 * linear or rotational velocity.
	 *
	 * @param loc The static of the Kinematic.
	 */
	Kinematic(const Staticff& loc)
	: Staticff(loc), velocity(), rotation(0)
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
	Kinematic(const Vector2df& position, double orientation,
			const Vector2df& velocity, double avel)
	: Staticff(position, orientation),
	velocity(velocity), rotation(avel)
	{}

	/**
	 * Zeros the static and velocity of this Kinematic.
	 */
	void clear()
	{
		Staticff::clear();
		velocity.clear();
		rotation = 0.0f;
	}

	/**
	 * Checks that the given Kinematic is equal to this.
	 * Kinematics are equal if their statics, velocities and
	 * rotations are equal.
	 */
	bool operator == (const Kinematic& other)
	{
		return position == other.position &&
		orientation == other.orientation &&
		velocity == other.velocity &&
		rotation == other.rotation;
	}

	/**
	 * Checks that the given Kinematic is unequal to this.
	 * Kinematics are unequal if any of their statics,
	 * velocities or rotations are unequal.
	 */
	bool operator != (const Kinematic& other)
	{
		return position != other.position ||
		orientation != other.orientation ||
		velocity != other.velocity ||
		rotation != other.rotation;
	}

	/**
	 * Checks that the given Kinematic is less than this.  A
	 * Kinematic is less than another Kinematic if its position
	 * along the x-axis is less than that of the other Kinematic.
	 */
	bool operator < (const Kinematic& other) const
	{
		return position.x < other.position.x;
	}

	/**
	 * Sets the value of this Kinematic to the given static.
	 * The velocity components of the Kinematic are left
	 * unchanged.
	 *
	 * @param other The Staticff to set the Kinematic to.
	 */
	Kinematic& operator = (const Staticff& other)
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
	void operator *= (double f);

	/**
	 * Trims the speed of the Kinematic to be no more than that
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
