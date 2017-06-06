#include "../include/main.h"
bool tank     = true;
bool wpressed = false;

void operatorControl() {
  sensors::reset();
  if (rerun::enabled)
    rerun::record();

  while (true) {
    if (tank) {
      drive::tank();
    } else if (!tank) {
      drive::accel::drive();
    }
    if (!wpressed && joystickGetDigital(1, 7, JOY_DOWN)) {
      tank = !tank;
    } else {
      wpressed = joystickGetDigital(1, 7, JOY_DOWN);
    }
    debug::debug();
    delay(50);
  }

  if (rerun::enabled)
    rerun::stop();
}
