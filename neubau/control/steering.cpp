/*
 * steering.cpp
 *
 *  Created on: 29-Mar-2009
 *      Author: fushunpoon
 */

#include "steering.h"

void Seek::getSteering(SteeringOutput* output)
{
	// First work out the direction
	output->linear = *target;
	output->linear -= robot->position;

	// If there is no direction, do nothing
	if (output->linear.squareMagnitude() > 0)
	{
		output->linear.normalize();
		output->linear *= maxAcceleration;
	}
}

void Flee::getSteering(SteeringOutput* output)
{
	// First work out the direction
	output->linear = robot->position;
	output->linear -= *target;

	// If there is no direction, do nothing
	if (output->linear.squareMagnitude() > 0)
	{
		output->linear.normalize();
		output->linear *= maxAcceleration;
	}
}

//SeekWithInternalTarget::SeekWithInternalTarget()
//{
//	// Make the target pointer point at our internal target.
//	target = &internal_target;
//}

void Wander::getSteering(SteeringOutput* output)
{
	// Make sure we have a target
	if (target->squareMagnitude() == 0) {
		internal_target = robot->position;
		internal_target.x += volatility;
	}

	Vector2df offset = *target - robot->position;
	real angle;
	if (offset.x*offset.x + offset.y*offset.y > 0) {
		// Work out the angle to the target from the robot
		angle = atan2(offset.y, offset.x);
	}
	else
	{
		// We're on top of the target, move it away a little.
		angle = 0;
	}

	// Move the target to the boundary of the volatility circle.
	internal_target = robot->position;
	internal_target.x += volatility * cos(angle);
	internal_target.y += volatility * sin(angle);

	// Add the turn to the target
	// TODO!! RANDOM vectors?!
	// internal_target.x += randomBinomial(turnSpeed);
	// internal_target.y += randomBinomial(turnSpeed);

	Seek::getSteering(output);
}
//
//void AvoidSphere::getSteering(SteeringOutput* output)
//{
//	// Clear the output, in case we don't write to it later.
//	output->clear();
//
//	// Make sure we're moving
//	if (robot->velocity.squareMagnitude() > 0)
//	{
//		// Find the distance from the line we're moving along to the obstacle.
//		Vector2dd movementNormal = robot->velocity.unit();
//		Vector2dd characterToObstacle = obstacle->position - robot->position;
//
//		real distanceSquared = characterToObstacle * movementNormal;
//		distanceSquared = characterToObstacle.squareMagnitude() -
//		distanceSquared*distanceSquared;
//
//		// Check for collision
//		real radius = obstacle->radius + avoidMargin;
//		if (distanceSquared < radius*radius)
//		{
//			// Find how far along our movement vector the closest pass is
//			real distanceToClosest = characterToObstacle * movementNormal;
//
//			// Make sure this isn't behind us and is closer than our lookahead.
//			if (distanceToClosest > 0 && distanceToClosest < maxLookahead)
//			{
//				// Find the closest point
//				Vector2dd closestPoint =
//					robot->position + movementNormal*distanceToClosest;
//
//				// Find the point of avoidance
//				internal_target =
//					obstacle->position +
//					(closestPoint - obstacle->position).unit() *
//					(obstacle->radius + avoidMargin);
//
//				// Seek this point
//				Seek::getSteering(output);
//			}
//		}
//	}
//}

void BlendedSteering::getSteering(SteeringOutput *output)
{
	// Clear the output to start with
	output->clear();

	// Go through all the behaviours in the list
	std::vector<BehaviourAndWeight>::iterator baw;
	real totalWeight = 0;
	SteeringOutput temp;
	for (baw = behaviours.begin(); baw != behaviours.end(); baw++)
	{
		// Make sure the children's robot is set
		baw->behaviour->robot = robot;

		// Get the behaviours steering and add it to the accumulator
		baw->behaviour->getSteering(&temp);
		output->linear += temp.linear * baw->weight;
		output->angular += temp.angular * baw->weight;

		totalWeight += baw->weight;
	}

	// Divide the accumulated output by the total weight
	if (totalWeight > 0.0)
	{
		totalWeight = (real)1.0 / totalWeight;
		output->linear *= totalWeight;
		output->angular *= totalWeight;
	}
}

void PrioritySteering::getSteering(SteeringOutput* output)
{
	// We'll need epsilon squared later.
	real epSquared = epsilon*epsilon;

	// Start with zero output, so if there are no behaviours in
	// the list, we'll output zero.
	output->clear();

	// Go through all the behaviours in the list
	std::vector<SteeringBehaviour*>::iterator b;
	for (b = behaviours.begin(); b != behaviours.end(); b++)
	{
		// Make sure the children's robot is set
		(*b)->robot = robot;

		// Get the steering result from this behaviour
		(*b)->getSteering(output);

		// Check if it is non zero.
		if (output->squareMagnitude() > epSquared)
		{
			// We have a result, so store it and exit.
			lastUsed = *b;
			return;
		}
	}
}
