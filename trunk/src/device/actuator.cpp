/*
 * actuator.cpp
 *
 *  Created on: 25-Feb-2009
 *      Author: fushunpoon
 */

/*
 * Uses EULER_INTEGRATION(duration), defined above.
 */
void OdometricLocator::integrate(float duration)
{
	EULER_INTEGRATION(duration, velocity, rotation);
}

/*
 * Uses EULER_INTEGRATION(duration), defined above.
 */
void OdometricLocator::integrate(const SteeringOutput& steer,
		float duration)
{
	BEEMAN_INTEGRATION(duration, position, velocity, steer.linear, acceleration, oldAcceleration);

	// NON BEEMAN method. Saves me having to store another field.
	rotation += steer.angular*duration;
}

