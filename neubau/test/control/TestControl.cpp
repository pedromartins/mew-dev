#include <unistd.h>
#include <device/actuator.h>
#include <device/sensor.h>
#include <electronic/arduino.h>

/*
Arduino * ar = new Arduino();
IDriveSystem ds;
IRSensor is(ar, 0);

bool frontIRcond() {
	return is < 30;
}

void goForwardUntil(bool (*cond)(void)) {
	ds.setPowerLevel(1.0, 0.0);
	while(!cond()) {
		usleep(10000);
	}
	ds.setPowerLevel(0.0, 0.0);
}


int main() {
	goForwardUntil(&frontIRcond);
	return 0;
}
*/

int main() {
	return 0;
}

/// TODO How might we control our robot, now that we have these separate
/// classes for motors, sensors, and things?