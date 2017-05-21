#include "motors.hpp"

void motor::set(int _power) {
  power = _power * inverted * scale;
  motors::slew::list[port].power = power;
}

namespace motors {
void set(motor _motor, int power) { _motor.set(power); }

int get(motor _motor) { return motorGet(_motor.port); }

motor init(unsigned char port, int inverted, long slewRate, float scale) {
  motor _motor;
  _motor.port = port;
  _motor.inverted = inverted;
  _motor.slewRate = slewRate;
  _motor.scale = scale;
  slew::list[_motor.port] = _motor;
  return _motor;
}

namespace slew {
motor list[11];
TaskHandle handle;

void _slew(void *none) {
  unsigned long int current;
  while (true) {
    current = millis();
    for (size_t i = 1; i <= 11; i++) {
      if (current - list[i].tlast < list[i].slewRate) {
        continue;
      }
      motorSet(list[i].port, list[i].power);
      list[i].tlast = current;
    }
  }
}

void init(void) {
  motor default_motor;
  default_motor.inverted = 1;
  default_motor.slewRate = 1;
  default_motor.scale = 0;
  for (size_t i = 1; i <= 11; i++) {
    default_motor.port = i;
    list[i] = default_motor;
  }
  handle = taskCreate(&_slew, TASK_DEFAULT_STACK_SIZE, NULL,
                      TASK_PRIORITY_DEFAULT + 1);
}
}
}
