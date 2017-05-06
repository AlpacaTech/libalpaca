#include "motors.h"

namespace motors {
  void set(motor _motor, int power) {
    motorSet(_motor.port, power * (_motor.inverted == true) ? -1 : 1);
  }

  int get(motor _motor) {
    return motorGet(_motor.port);
  }

  void init(motor* _motor, unsigned char port, bool inverted, long slewRate) {
    _motor->port = port;
    _motor->inverted = inverted;
    _motor->slewRate = slewRate;
  }
}
