#ifndef VIRTUAL_PERCEPTOR_H
#define VIRTUAL_PERCEPTOR_H

#include <map>

/// TODO Use perceptors.
/*
 * This class basically gets the sensor readings and transforms them into useful data
*/


class Perceptor{

public:
	Perceptor(){
	  SimulatedLocator * loc = new SimulatedLocator();
	  locators[loc] = 1.0;

	  SimulatedOrientator * or = new SimulatedOrientator();
	  orientators[or] = 1.0;
	}
}

#endif //VIRTUAL_PERCEPTOR_H_
