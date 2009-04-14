/*
 * floating.h
 *
 *  Created on: 06-Apr-2009
 *      Author: fushunpoon
 */

#ifndef FLOATING_H_
#define FLOATING_H_

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// an arbitrary equivalence tolerance, enough for most cases, I would think.
#define DEFAULT_SINGLE_TOLERANCE 0.002
#define DEFAULT_DOUBLE_TOLERANCE 0.00001

/**
 * This is a floating point equivalence function.
 * Returns true iff the two floating point operands are close enough.
 * Very expensive if used extensively.
 *
 * @return
 */
bool inline fequals(float a, float b, double tolerance=DEFAULT_SINGLE_TOLERANCE) {
	return fabs(a-b)<tolerance;
}
bool inline equals(double a, double b, double tolerance=DEFAULT_DOUBLE_TOLERANCE) {
	return fabs(a-b)<tolerance;
}

/**
 * Returns a random double!
 * @return
 */
double inline randDouble() {
	return rand()/((double)RAND_MAX + 1);
}

#endif /* FLOATING_H_ */
