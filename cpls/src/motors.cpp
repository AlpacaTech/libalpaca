#include "motors.hpp"

void motor_t::set(int _power) {
  power = _power * inverted * scale;
  motors::slew::list[port].power = power;
}

namespace motors {
void set(motor_t motor, int power) { motor.set(power); }

int get(motor_t motor) { return motorGet(motor.port); }

motor_t init(unsigned char port, int inverted, long slewRate, float scale) {
  motor_t motor;
  motor.port = port;
  motor.inverted = inverted;
  motor.slewRate = slewRate;
  motor.scale = scale;
  slew::list[motor.port] = motor;
  return motor;
}

namespace slew {
motor_t list[11];
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
  motor_t default_motor;
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
