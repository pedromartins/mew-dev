/*
 * Robot.hpp
 *
 *  Created on: 03-Feb-2009
 *      Author: fushunpoon
 */

#ifndef ROBOT_HPP_
#define ROBOT_HPP_

#define NUM_LOCATORS	5
#define NUM_ORIENTATORS	5
#define NUM_SPEDOMETERS	5
#define NUM_AVS			5	// number of angular velocimeters

/**
 * RobotState
 *
 * Represents the state of the robot at any one time.
 * This class should be updated as frequently as possible,
 * and definitely should be updated before any computation
 * on the RobotState is performed.
 *
 * Design decision: Do we use arrays to hold the ILocators
 * and IOrientators etc. or do we use STL?
 */
class RobotState {
	Point2df location;
	float orientation;
	float speed;
};

/**
 * Robot
 *
 * An abstract class to represent the generic robot.
 * Any Robot must keep track of its state by updating it.
 * Other functionalities are provided by subclasses.
 *
 * TODO make room for managing an running programs.
 */
class Robot {
public:
	Robot() {
		initLocators();
		initOrientators();
		initSpedometers();
		initAngularVelocimeters();
	}
	virtual ~Robot();

	// update the state of this robot.
	virtual void updateState() = 0;

	// starts a program running.
	virtual void startProgram();
protected:
	virtual void initLocators() = 0;
	virtual void initOrientators() = 0;
	virtual void initSpedometers() = 0;
	virtual void initAngularVelocimeters() = 0;
private:
	RobotState state;
	ILocator locators[NUM_LOCATORS];
	IOrientator orientators[NUM_ORIENTATORS];
	ISpedometer spedometers[NUM_SPEDOMETERS];
	IAngularVelocimeter angularVelocimeters[NUM_AVS];
};

class TempleBuildingRobot {

};

#endif /* ROBOT_HPP_ */
