#include "main.h"
static const bool tank = true;

void operatorControl() {
  sensors::reset();
  if (rerun::enabled)
    rerun::record();

  while (true) {
    if (tank) {
      drive::tank();
    } else {
      drive::accel::drive();
    }
    debug::debug();
    delay(50);
  }

  if (rerun::enabled)
    rerun::stop();
}
