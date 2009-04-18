#ifndef PERCEPTOR_H
#define PERCEPTOR_H

#include "model.h"
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
 * For both, information can be interpreted to update the:
 * - Internal state (PRIORITY)
 * - External state
 *
 * Terminology: A xxxDeltor is a PROVIDER for 'delta's (i.e. changes) in a
 * particular piece of information.
 *
 * Thus, we separate the DATA PROVIDERS from INFORMATION PROVIDERS.
 * DATA providers give raw data, raw integer values, in some sort of measurement.
 * These measurements are accumulated if required, and the value accumulated
 * is interpreted in the context of a particular model only when it is sensible.
 * Due to the simplicity of the task, one can expect that some direct implementations
 * to Information providers are written.
 *
 * Perceptor:   Updates the model using the latest information available.
 * -= Information Providers =-
 * ILocator:    Updates the raw location of the robot
 * IOrientator: Updates the raw orientation of the robot
 * (IVelocimeter) : Updates the raw velocity of the robot
 * (IAngularVelocimeter) : Updates the raw angular velocity of the robot
 * IProximityDetector: updates raw proximity information
 *
 * -= Data Providers =-
 * IDeltor<T>: A templated interface class for changes to a type T.
 * Specializations include:
 *   IVectorDeltor<T>: Provides a change in a pair of values last invocation.
 *   IFloatDeltor:  Provides a change in a floating point value since last invocation
 *   IIntDeltor: Provides the change in an calar value since last invocation
 *
 */
typedef Static<float,Orientation> RawStatic;

class Perceptor {
public:
	/**
	 * Builds a perceptor with a reference to a model.
	 * Might use
	 * @param model
	 * @return
	 */
	Perceptor(Model model){
		/*
      ExampleLocator * loc = new ExampleLocator();
      locators[loc] = 0.2;

      ExampleOrientator * or = new ExampleOrientator();
      orientators[or] = 0.2;
		 */
	}

	/**
	 * Queries all the information sources that this Perceptor knows about
	 * and updates the internal state of the perceptor.
	 */
	void updateInternalState() {

	}

	/**
	 *
	 */
	void updateModel() {

	}


	/**
	 * Iterates over
	 * @return
	 */
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

protected:
	// The 'raw' internal state of the robot.
	RawStatic internalstate;
private:
	std::map<ILocator *, float> locators;
	std::map<IOrientator *, float> orientators;

}

#endif //PERCEPTOR_H_
