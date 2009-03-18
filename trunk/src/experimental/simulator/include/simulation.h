/*
 * simulation.h
 *
 *
 * A simulation is a test program that sets up robot(s) with a particular
 * models, and worlds, such that we can see the behaviours of our robot
 *
 *  Created on: 04-Mar-2009
 *      Author: fushunpoon
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

class Simulation {
public:
	Simulation();
	virtual ~Simulation();

	void run(); // run the simulation.
private:
	GridModel *model;
	SimulatedRobot *robot;
	SimulatedWorld *world;
};

#endif /* SIMULATION_H_ */
