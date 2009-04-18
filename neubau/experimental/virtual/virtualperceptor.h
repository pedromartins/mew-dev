#ifndef VIRTUAL_PERCEPTOR_H
#define VIRTUAL_PERCEPTOR_H

#include <map>

/// TODO Use perceptors.


/**
 * Types of data:
 * The types of data that is harvested from available sensors come in two
 * forms:
 * - "absolute" data
 * - "time-depenedent and relative" data
 *
 * Absolute data includes:
 * - readings of ultrasound sensors: cm-distance from nearest detectable object
 *   PROVIDES: where we are with respect to the walls of the world.
 * - readings of the compass: deci-degrees of the direction the robot is facing
 *   PROVIDES: what direction the robot is facing at any one time.
 *
 * Absolute data can be translated into useful information in the model directly
 * without dependency on any state, or other pieces of information.
 *
 * Relative data includes:
 * - mouse-tracking devices which give a dx/dy reading, dx/dy being pixels
 *   moved since last queried.
 *   DEPENDS:  where the robot last was
 *   PROVIDES: where the robot now is.
 * - IR sensors: detects objects proximity in range of robot
 *   DEPENDS:  where the robot is
 *   PROVIDES: accessibility information of neighbouring areas.
 *
 * To interpret relative data, it MUST be combined with some previously stored
 * state to be translated into a useful form, which then must be interpreted
 * by the model.
 *
 * The state is stored where???
 *
 *
 * Thus, we separate the DATA PROVIDERS from INFORMATION PROVIDERS.
 * DATA providers give raw data, raw integer values, in some sort of measurement.
 * These measurements are accumulated if required, and the value accumulated
 * is interpreted in the context of a particular model only when it is sensible.
 *
 *
 */
class Perceptor {

public:
	Perceptor(){
		/*
      ExampleLocator * loc = new ExampleLocator();
      locators[loc] = 0.2;

      ExampleOrientator * or = new ExampleOrientator();
      orientators[or] = 0.2;
		 */
	}

	float getOrientation() {
		float orientation = 0.0f;
		for(std::map<ILocator *, float>::iterator iter = orientators.begin();
		iter != orientators.end(); iter++) {
			location += (*iter).first()->getOrientation() * (*iter).second();
		}
		return location;
	}

	Vector2df getLocation() {
		Vector2df location = new Vector2df();
		for(std::map<ILocator *, float>::iterator iter = locators.begin();
		iter != locators.end(); iter++) {
			orientators += (*iter).first()->getOrientation() * (*iter).second();
		}
		return location;
	}

private:
	std::map<ILocator *, float> locators;
	std::map<IOrientator *, float> orientators;

}

#endif //VIRTUAL_PERCEPTOR_H_
