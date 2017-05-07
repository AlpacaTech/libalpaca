#include "motors.h"


motor::motor() {

}

void motor::set(int _power) {
  power = _power * inverted * scale;
  motorSet(port, power);
}

namespace motors {
  motor list[11];

  void set(motor* _motor, int power) {
    _motor->set(power);
  }

  int get(motor* _motor) {
    return motorGet(_motor->port);
  }

  motor* init(unsigned char port, char inverted, long slewRate, float scale) {
    motor _motor;
    _motor.port = port;
    _motor.inverted = inverted;
    _motor.slewRate = slewRate;
    _motor.scale = scale;
    list[port] = _motor;
    return &list[_motor.port];
  }

  namespace slew {
    TaskHandle slewHandle;
    motor default_motor;

    void task(void *none) {
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
      default_motor.inverted = 1;
      default_motor.slewRate = 1;
      default_motor.scale = 0;
      for (size_t i = 1; i <= 11; i++) {
        default_motor.port = i;
        list[i] = default_motor;
      }
      slewHandle = taskCreate(&task, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT + 1);
    }
  }
}
