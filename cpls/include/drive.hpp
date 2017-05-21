#pragma once
#include "motors.hpp"
#include "sensors.hpp"

namespace drive {
struct side {
  motor topM;
  motor midM;
  motor lowM;
  void set(int power);
  sensors::quad *sensor;
};
extern double inch;
extern side left;
extern side right;
void set(int lpower, int rpower);
void init(void);
void tank(void);
void inches(long inches);
}
