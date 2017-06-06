#pragma once
#include "motors.hpp"
#include "sensors.hpp"

namespace drive {
struct side_t {
  motor_t topM;
  motor_t midM;
  motor_t lowM;
  void set(int power);
  sensors::quad_t* sensor;
};
extern double inch;
extern side_t left;
extern side_t right;
/* Set both sides of the drive at their requested powers
 */
void set(int lpower, int rpower);
void init(void);
/* Tank control that can (and should) be in a while loop
 */
void tank(void);
namespace accel {
extern int x;
extern int y;
extern int prevX;
extern int prevY;
void drive(void);
}
/* Drive a specific number of inches
 */
void inches(long inches);
}
