/*
 * simulatedlocator.h
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#ifndef SIMULATEDLOCATOR_H_
#define SIMULATEDLOCATOR_H_

class SimulatedLocator : public ILocator<int> {
public:
	SimulatedLocator();
	virtual ~SimulatedLocator();
};

#endif /* SIMULATEDLOCATOR_H_ */
