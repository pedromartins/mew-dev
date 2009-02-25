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

#include "include/kinematic.h"

namespace mew {
namespace core {


/*
 * Uses EULER_INTEGRATION(duration), defined above.
 */
void Static::integrate(const SteeringOutput& steer, float duration)
{
	EULER_INTEGRATION(duration, steer.linear, steer.angular);
}

void Static::setOrientationFromVelocity(const Vector2df& velocity)
{
	// If we haven't got any velocity, then we can do nothing.
	if (velocity.squareMagnitude() > 0) {
		orientation = atan2(velocity.Y, velocity.X);
	}
}

float Static::getOrientationFromVelocity(const Vector2df& velocity)
{
	return atan2(velocity.Y, velocity.X);
}

Vector2df Static::getOrientationAsVector() const
{
	return Vector2df(cos(orientation),sin(orientation));
}


/* Add and divide used in finding Kinematic means. */
void Kinematic::operator += (const Kinematic& other)
{
	position+=other.position;
	velocity+=other.velocity;
	rotation+=other.rotation;
	orientation+=other.orientation;
	acceleration+=other.acceleration;
}

void Kinematic::operator -= (const Kinematic& other)
{
	position-=other.position;
	velocity-=other.velocity;
	rotation-=other.rotation;
	orientation-=other.orientation;
	acceleration-=other.acceleration;
}

void Kinematic::operator *= (float f)
{
	position*=f;
	velocity*=f;
	rotation*=f;
	orientation*=f;
	acceleration*=f;
}


/** Ensures that the velocity does not go out of the range of sensible and workable velocities. */
void Kinematic::trimMaxSpeed(float maxSpeed)
{
	if (velocity.squareMagnitude() > maxSpeed*maxSpeed) {
		velocity.normalise();
		velocity *= maxSpeed;
	}
}

/** Ensures that the acceleration does not go out of range of sensible and workable accelerations. */
void Kinematic::trimMaxAcceleration(float maxAcceleration)
{
	if (acceleration.squareMagnitude() > maxAcceleration* maxAcceleration) {
		acceleration.normalize();
		acceleration *= maxAcceleration;
	}
}

void Kinematic::setOrientationFromVelocity()
{
	// If we haven't got any velocity, then we can do nothing.
	if (velocity.squareMagnitude() > 0) {
		orientation = atan2(velocity.x, velocity.z);
	}
}

} // END of namespace core
} // END of namespace mew
