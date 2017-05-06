#include "main.h"

namespace drive {
  side left;
  side right;

  void init(void) {
    motors::init(&left.topM, 2, false, 127);
    motors::init(&left.lowM, 3, true, 127);
    motors::init(&left.lowM, 4, false, 127);
    motors::init(&left.topM, 7, true, 127);
    motors::init(&left.lowM, 8, false, 127);
    motors::init(&left.lowM, 9, true, 127);
    left.sensor = &sensors::left;
    right.sensor = &sensors::right;
  }

  void side::set(int power) {
    motors::set(side::topM, power);
    motors::set(side::midM, power);
    motors::set(side::lowM, power);
  }

  void set(int lpower, int rpower) {
    left.set(lpower);
    right.set(rpower);
  }

  void tank(void) {
    int deadband = 10;
    int lj = joystickGetAnalog(1, 3);
    int rj = joystickGetAnalog(1, 2);
    if (lj < deadband && rj < deadband)
      return;
    lj = (lj < deadband) ? 0 : lj;
    rj = (rj < deadband) ? 0 : rj;
    pid::enabled[0] = (lj == 0);
    pid::enabled[1] = (rj == 0);
    if (lj != 0)
      left.set(lj);
    if (rj != 0)
      right.set(rj);
    pid::request((lj == 0) ? left.sensor->request : left.sensor->value(), (rj == 0) ? right.sensor->request : right.sensor->value());
  }
}
