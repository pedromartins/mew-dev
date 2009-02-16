/*
 * Defines the classes used for steering.
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
#ifndef AICORE_STEERING_H
#define AICORE_STEERING_H

namespace mew {
namespace movement{

/**
 * The steering behaviour is the base class for all dynamic
 * steering behaviours.
 */
class SteeringBehaviour
{
public:
	/**
	 * The robot that is moving.
	 */
	Kinematic *robot;

	/**
	 * Works out the desired steering and writes it into the given
	 * steering output structure.
	 */
	virtual void getSteering(SteeringOutput* output) const = 0;
};


// Concrete classes

/**
 * The seek steering behaviour takes a target and aims right for
 * it with maximum acceleration.
 */
class Seek : public SteeringBehaviour
{
public:
	/**
	 * The target may be any vector (i.e. it might be something
	 * that has no orientation, such as a point in space).
	 */
	Vector3 *target;

	/**
	 * The maximum acceleration that can be used to reach the
	 * target.
	 */
	real maxAcceleration;

	/**
	 * Works out the desired steering and writes it into the given
	 * steering output structure.
	 */
	virtual void getSteering(SteeringOutput* output) const;
};

/**
 * The seek steering behaviour takes a target and aims in the
 * opposite direction with maximum acceleration.
 */
class Flee : public Seek
{
public:
	/**
	 * Works out the desired steering and writes it into the given
	 * steering output structure.
	 */
	virtual void getSteering(SteeringOutput* output) const;
};



} // END of namespace movement
} // END of namespace mew

#endif // AICORE_STEERING_H
