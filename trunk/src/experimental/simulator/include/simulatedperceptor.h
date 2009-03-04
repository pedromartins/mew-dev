#ifndef _SIMULATED_PERCEPTOR_H
#define _SIMULATED_PERCEPTOR_H

#include <map>
#include <perceptor.h>

class SimulatedPerceptor : public Perceptor {

public:
	SimulatedPerceptor(){
	  SimulatedLocator * loc = new SimulatedLocator();
	  locators[loc] = 1.0;

	  SimulatedOrientator * or = new SimulatedOrientator();
	  orientators[or] = 1.0;
	}
}

#endif //_SIMULATED_PERCEPTOR_H_
