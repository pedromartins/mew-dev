/*
 * sensor.h
 *
 *  Created on: 01-Apr-2009
 *      Author: fushunpoon
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include <electronic/arduino.h>
#include <iostream>

using namespace std;


/**
 * A single sensor must provide at least a single sensor
 * reading.
 * Operators have been overloaded for convenience.
 *
 * getReading() for each of the sensors is expected to return
 * the latest possible reading from the physical sensor:
 * if it has been polled too frequently, it is getReading's
 * responsibility to return a buffered value for the time being.
 */
class Sensor {
public:
	virtual ~Sensor(){}

	bool operator < (int n) { return getReading() < n; }
	bool operator > (int n) { return getReading() > n; }
	bool operator <= (int n) { return getReading() <= n; }
	bool operator >= (int n) { return getReading() >= n; }
	bool operator == (int n) { return getReading() == n; }
	bool operator != (int n) { return getReading() != n; }

	virtual int getReading() = 0;
};


/************************************
 * Series of Arduino-based devices
 **/

class IRSensor : public Sensor {
public:
	IRSensor(Arduino *ard, int num): ard(ard), num(num){
		if (num <= 0 || num > 3 ) {
			cerr << "Error: Oh dear, invalid IRsensor number provided in constructor" <<endl;
		}
	}
	virtual ~IRSensor(){}

protected:

	virtual int getReading() {
		int buff[4];

		ard->getIRreadings(buff);

		return buff[num];
	}
private:
	Arduino *ard;
	int num;
};


class USSensor : public Sensor {
public:
	USSensor(Arduino *ard, int num): ard(ard), num(num){
		if (num <= 0 || num > 1 ) {
			cerr << "Error: Oh dear, invalid USsensor number provided in constructor" <<endl;
		}
	}
	virtual ~USSensor(){}

protected:

	virtual int getReading() {
		int buff[2];

		ard->getUSreadings(buff);

		return buff[num];
	}

private:
	Arduino *ard;
	int num;
};


class Compass :public Sensor {
public:
	Compass(Arduino *ard): ard(ard){}
	virtual ~Compass() {}


	virtual int getReading() {
		return ard->getCompassreading();
	}

private:
	Arduino *ard;
};


#endif /* SENSOR_H_ */
