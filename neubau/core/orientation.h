/*
 * orientation.h
 *
 *  Created on: 18-Apr-2009
 *      Author: fushunpoon
 */

#ifndef ORIENTATION_H_
#define ORIENTATION_H_

#include <core/vector2d.h>

/**
 * SimpleOrientation: can only take values of right angles
 */
typedef enum SimpleOrientation {
	NORTH=0, WEST, SOUTH, EAST
} SimpleOrientation;



/**
 * Deci-degree accurate bearing-class. Wraps around any needed
 *
 * Provides Orientation-difference (shortest/smallest angle)
 * Mapping of one Orientation system onto another, converting its stored
 * value between them.
 *
 * Ranges over (-1800,1800].
 *
 * TODO hard-core implementation of this class
 */
class ComplexOrientation {
public:

	/**
	 * Constructs a Complex Orientation using a floating point number
	 * in deci-degrees for an initial value.
	 * @param
	 * @return
	 */
	ComplexOrientation(float val): val(val) {
		//TODO constructor
	}

	ComplexOrientation(Vector2df) {
		//TODO constructor of Orientation
	}

	/**
	 * Makes this Orientation point the other way (== rotateCW(1800))
	 */
	void invert();

	/**
	 * Rotates this Orientation object around by amount deci-degrees
	 * clockwise.
	 * @param amount
	 */
	void rotateCW(float amount);

	/**
	 * Rotates this Orientation object around by amount deci-degrees
	 * counter-clockwise.
	 * @param amount
	 */
	void rotateCCW(float amount);

	/**
	 * Finds the (shortest) difference between this and the given angle.
	 * @param rhs
	 * @return
	 */
	ComplexOrientation operator-(const ComplexOrientation& rhs);

	/**
	 * Returns true iff rhs is on the clockwise half of this orientation.
	 * @param rhs
	 * @return
	 */
	bool operator<(const ComplexOrientation& rhs);

	/**
	 * Returns true iff rhs is on the counter-clockwise half of this
	 * orientation.
	 * @param rhs
	 * @return
	 */
	bool operator>(const ComplexOrientation& rhs);

	/**
	 * Returns true iff rhs is equal to, or is on the clockwise half of
	 * this orientation.
	 * @param rhs
	 * @return
	 */
	bool operator<=(const ComplexOrientation& rhs);

	/**
	 * Returns true iff rhs is equal to, or is on the counter-clockwise
	 * half of this orientation.
	 * @param rhs
	 * @return
	 */
	bool operator>=(const ComplexOrientation& rhs);


	/**
	 * Get a unit vector pointing in the same direction as this Orientation
	 * @return a unit vector pointing the same way.
	 */
	Vector2df getUnitVector();

private:
	float val; // internal store
};

typedef SimpleOrientation Orientation;

#endif /* ORIENTATION_H_ */
