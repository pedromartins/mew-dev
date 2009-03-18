/*
 * simulatedlocator.h
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#ifndef SIMULATEDLOCATOR_H_
#define SIMULATEDLOCATOR_H_

#include <estimator.h>
#include <entity.h>
#include <simulatedworld.h>

/**
 * SimulatedLocator
 *
 * A simple locator 'sensor' for a simulated robot.
 * It happens that the simulator can tap directly into the world's information
 * and therefore the location returned is actually perfect.
 */
class SimulatedLocator : public ILocator<int> {
public:
	SimulatedLocator(Entity * entity, SimulatedWorld * world)
	:entity(entity),world(world){}

	virtual ~SimulatedLocator();

	/** Returns the location */
	int getLocation() const {
		return world->getLocationOf(entity);
	};

private:
	Entity *entity;
	SimulatedWorld *world;
};

#endif /* SIMULATEDLOCATOR_H_ */
