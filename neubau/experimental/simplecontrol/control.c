
#include "actuator.h"
#include "sensor.h"

DriveSystem ds;
IRSensor is;

bool frontIRcond() {
  return is < 30;
}

void goForwardUntil(bool *cond(void)) {
  ds->setPowerLevel(1.0, 0.0);
  while(!cond()) {
    usleep(10000)
  }
  ds->setPowerLevel(0.0, 0.0);
}

void main() {
  goForwardUntil(&frontIRCond);
}
