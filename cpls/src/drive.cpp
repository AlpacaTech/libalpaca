#include "main.h"

namespace drive {
  side left;
  side right;
  double inch = 28.64788975654116043839907740705258516620273623328216077458012735;

  void side::set(int power) {
    motors::set(side::topM, power);
    motors::set(side::midM, power);
    motors::set(side::lowM, power);
  }

  void init(void) {
    left.topM = motors::init(2, 1, 127, .8);
    left.midM = motors::init(3, -1, 127, .8);
    left.lowM = motors::init(4, 1, 127, .8);
    right.topM = motors::init(7, -1, 127, .8);
    right.midM = motors::init(8, 1, 127, .8);
    right.lowM = motors::init(9, -1, 127, .8);
    left.sensor = &sensors::left;
    right.sensor = &sensors::right;
  }

  void set(int lpower, int rpower) {
    left.set(lpower);
    right.set(rpower);
  }

  void tank(void) {
    int deadband = 20;
    int lj = joystickGetAnalog(1, 3);
    int rj = joystickGetAnalog(1, 2);
    if (abs(lj) < deadband && abs(rj) < deadband) {
      pid::enabled[0] = true;
      pid::enabled[1] = true;
      return;
    }
    lj = (abs(lj) < deadband) ? 0 : lj;
    rj = (abs(rj) < deadband) ? 0 : rj;
    pid::enabled[0] = (lj == 0);
    pid::enabled[1] = (rj == 0);
    if (lj != 0)
      left.set(lj);
    if (rj != 0)
      right.set(rj);
    pid::request((lj == 0) ? left.sensor->request : left.sensor->value(), (rj == 0) ? right.sensor->request : right.sensor->value());
  }

  void inches(long inches) {
    pid::enable();
    left.sensor->request += inches * inch;
    right.sensor->request += inches * inch;
    pid::wait(pid::default_precision, inches * inches * 8);
  }
}
