#include "sensors.h"

void _lreset() {
  encoderReset(left.self);
}

void _rreset() {
  encoderReset(right.self);
}

long _lget() {
  return encoderGet(left.self);
}

long _rget() {
  return encoderGet(right.self);
}

void quadInit() {
  left.ports[0] = 1;
  left.ports[1] = 2;
  right.ports[0] = 3;
  right.ports[1] = 4;
  left.inverted = 1;
  right.inverted = -1;
  left.self = encoderInit(left.ports[0],left.ports[1], (left.inverted != 1));
  right.self = encoderInit(right.ports[0],right.ports[1], (right.inverted == 1));
  left.value = &_lget;
  right.value = &_rget;
  left.zero = left.value();
  right.zero = right.value();
  left.reset = &_lreset;
  right.reset = &_rreset;

}
