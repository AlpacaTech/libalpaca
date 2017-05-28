#pragma once
#include "motors.hpp"
#include "sensors.hpp"

namespace drive {
struct side_t {
  motor_t topM;
  motor_t midM;
  motor_t lowM;
  void set(int power);
  sensors::quad_t *sensor;
};
extern double inch;
extern side_t left;
extern side_t right;
void set(int lpower, int rpower);
void init(void);
void tank(void);
namespace accel {
extern long x;
extern long y;
extern long prevX;
extern long prevY;
void drive(void);
}
void inches(long inches);
}
