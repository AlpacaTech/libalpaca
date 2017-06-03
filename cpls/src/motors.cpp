#include "../include/motors.hpp"

void motor_t::set(int _power) {
  power                          = _power * inverted * scale;
  motors::slew::list[port].power = power;
}

namespace motors {
void set(motor_t motor, int power) { motor.set(power); }

int get(motor_t motor) { return motorGet(motor.port); }

motor_t init(unsigned char port, int inverted, float slewRate, float scale) {
  motor_t motor;
  motor.port             = port;
  motor.inverted         = inverted;
  motor.slewRate         = slewRate;
  motor.scale            = scale;
  slew::list[motor.port] = motor;
  return motor;
}

namespace slew {
motor_t list[11];
TaskHandle handle;

void _slew(void* none) {
  unsigned long int current;
  while (true) {
    current = millis();
    for (size_t i = 1; i <= 10; i++) {
      motorSet(i, (int)(((list[i].power - motorGet(i)) * list[i].slewRate) +
                        (current - list[i].tlast - slewWait) + motorGet(i)));
      list[i].tlast = current;
    }
    delay(slewWait);
  }
}

void init(void) {
  motor_t default_motor;
  default_motor.inverted = 1;
  default_motor.slewRate = 1;
  default_motor.scale    = 0;
  for (size_t i = 1; i <= 11; i++) {
    list[i]            = default_motor;
    default_motor.port = i;
  }
  handle = taskCreate(&_slew, TASK_DEFAULT_STACK_SIZE, NULL,
                      TASK_PRIORITY_DEFAULT + 1);
}
}
}
