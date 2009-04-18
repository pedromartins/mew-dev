#ifndef STATIC_H_
#define STATIC_H_

#include <iostream>
#include "vector2d.h"

using namespace std;

/**
 * Represents the static of a robot or other object.
 *
 * A static consists of a position and orientation.
 * Position is stored as a vector of type P,
 * Orientation is stored as a single value of type O.
 */
template <typename P, typename O>
class Static {
public:
	/**
	 * The position in 2D Euclidean space.
	 */
	Vector2d<P> position;

	/**
	 * The orientation, as a euler angle in radians around the
	 * positive y axis (i.e. up) from the positive z axis.
	 */
	O orientation;

	/**
	 * Creates a static with the given position and orientation.
	 */
	Static(const Vector2d<P>& position=Vector2d<P>(0,0), O orientation=(O)0)
	: position(position), orientation(orientation)
	{}

	/**
	 * Creates a static with the position vector given as
	 * components and the given orientation.
	 */
	Static(P x, P y, O orientation=(O)0)
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
		orientation = (O)0;
	}

	/**
	 * Checks that the given static is equal to this. Statics
	 * are equal if their positions and orientations are equal.
	 */
	bool operator == (const Static& other) const
	{
		return position == other.position && orientation == other.orientation;
	}

	/**
	 * Checks that the given static is unequal to
	 * this. Statics are unequal if either their positions or
	 * orientations are unequal.
	 */
	bool operator != (const Static& other) const
	{
		return position != other.position || orientation != other.orientation;
	}

	/**
	 * Sets the orientation of this static so it points along
	 * the given velocity vector.
	 * TODO this is not a good definition! Write this method over!
	 * @param velocity
	 */
	void setOrientationFromVelocity(const Vector2d<P>& velocity){
		// if x becomes 0, then we have either positive or negative infinity for y/x
		// giving atan thereof a value of 1 and -1 respectivity.
		// orientation = atan2(velocity.y,velocity.x);
	}

	/**
	 * Gets the current orientation and finds a unit vector pointing
	 * in the same direction on the x,y plane.
	 * TODO this is not a good definition! Write this method over!
	 * @return
	 */
	inline Vector2d<P> getOrientationAsVector() const {
		// return Vector2d<P>(cos(orientation),sin(orientation));
		return Vector2d<P>(0,0);
	}

	/**
	 * Fills the passed matrix with the Static's transformation.
        void retrieveTM(Matrix& m);
	 */
	template<typename X,typename Y>
	friend ostream& operator<<(ostream& os, const Static<X,Y>& rhs);
};

template<typename X,typename Y>
ostream& operator<<(ostream& os, const Static<X,Y>& rhs) {
	return os << "{" << rhs.position << "," << rhs.orientation << "}";
}

#endif
