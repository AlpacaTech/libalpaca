#pragma once
#include "sensors.h"
#include "motors.h"

namespace drive {
  class side {
  public:
    motor topM;
    motor midM;
    motor lowM;
    void set(int power);
    sensors::quad* sensor;
  };
  extern side left;
  extern side right;
  void set(int lpower, int rpower);
  void init(void);
  void tank(void);
}
