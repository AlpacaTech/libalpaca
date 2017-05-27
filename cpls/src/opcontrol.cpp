#include "main.h"

void operatorControl() {
  sensors::reset();
  if (rerun::enabled)
    rerun::record();

  while (true) {
    drive::tank();
    debug::debug();
    delay(50);
  }

  if (rerun::enabled)
    rerun::stop();
}
