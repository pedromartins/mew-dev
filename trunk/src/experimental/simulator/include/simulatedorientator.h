/*
 * simulatedorientator.h
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#ifndef SIMULATEDORIENTATOR_H_
#define SIMULATEDORIENTATOR_H_

class SimulatedOrientator : public IOrientator {
public:
	SimulatedOrientator(Entity * entity, SimulatedWorld * world)
	:entity(entity),world(world){}

	virtual ~SimulatedOrientator();

	/** Returns the location */
	float getOrientation() const {
		return world->getOrientationOf(entity);
	};

private:
	Entity *entity;
	SimulatedWorld *world;
};

#endif /* SIMULATEDORIENTATOR_H_ */
