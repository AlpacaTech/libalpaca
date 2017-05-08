#include "motors.h"

void motor::set(int power) {
  motorSet(port, power * inverted * scale);
}

namespace motors {
  void set(motor _motor, int power) {
    _motor.set(power);
  }

  int get(motor _motor) {
    return motorGet(_motor.port);
  }

  motor init(unsigned char port, int inverted, long slewRate, float scale) {
    motor _motor;
    _motor.port = port;
    _motor.inverted = inverted;
    _motor.slewRate = slewRate;
    _motor.scale = scale;
    return _motor;
  }
}
