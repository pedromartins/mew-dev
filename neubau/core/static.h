#ifndef STATIC_H_
#define STATIC_H_

#include "vector2d.h"

/**
 * Represents the static of a robot or other object.
 *
 * A static consists of a position and orientation. Position is
 * stored as a vector, rotation is a planar rotation about the y
 * axis. This will be altered to be a quaternion in due course.
 */
struct Static
{
	/**
	 * The position in 2D Euclidean space.
	 */
	Vector2df position;

	/**
	 * The orientation, as a euler angle in radians around the
	 * positive y axis (i.e. up) from the positive z axis.
	 */
	double orientation;

	/**
	 * Creates a new static with a 0 position and orientation.
	 */
	Static() : orientation(0)
	{}

	/**
	 * Creates a static at the given position with no rotation.
	 */
	Static(const Vector2df& position)
	: position(position), orientation(0)
	{}

	/**
	 * Creates a static with the given position and orientation.
	 */
	Static(const Vector2df& position, double orientation)
	: position(position), orientation(orientation)
	{}

	/**
	 * Creates a static with the position vector given as
	 * components and the given orientation.
	 */
	Static(double x, double y, double orientation)
	: position(x, y), orientation(orientation)
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
		orientation = 0;
	}

	/**
	 * Checks that the given static is equal to this. Statics
	 * are equal if their positions and orientations are equal.
	 */
	bool operator == (Static& other)
	{
		return position == other.position &&
		orientation == other.orientation;
	}

	/**
	 * Checks that the given static is unequal to
	 * this. Statics are unequal if either their positions or
	 * orientations are unequal.
	 */
	bool operator != (Static& other)
	{
		return position != other.position ||
		orientation != other.orientation;
	}

	/**
	 * Sets the orientation of this static so it points along
	 * the given velocity vector.
	 */
	void setOrientationFromVelocity(const Vector2df& velocity);

	/**
	 * Returns a unit vector in the direction of the current
	 * orientation.
	 */
	Vector2df getOrientationAsVector() const;

	/**
	 * Fills the passed matrix with the Static's transformation.
        void retrieveTM(Matrix& m);
	 */
};

#endif
