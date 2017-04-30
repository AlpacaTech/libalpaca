#include "main.h"

void _lreset() {
  encoderReset(sensors::left.self);
}

void _rreset() {
  encoderReset(sensors::right.self);
}

long _lget() {
  return encoderGet(sensors::left.self);
}

long _rget() {
  return encoderGet(sensors::right.self);
}

void sensors::init(void) {
  sensors::left.ports[0] = 1;
  sensors::left.ports[1] = 2;
  sensors::right.ports[0] = 3;
  sensors::right.ports[1] = 4;
  sensors::left.inverted = 1;
  sensors::right.inverted = -1;
  sensors::left.self = encoderInit(left.ports[0],left.ports[1], (left.inverted != 1));
  sensors::right.self = encoderInit(right.ports[0],right.ports[1], (right.inverted == 1));
  sensors::left.value = &_lget;
  sensors::right.value = &_rget;
  sensors::left.zero = left.value();
  sensors::right.zero = right.value();
  sensors::left.reset = &_lreset;
  sensors::right.reset = &_rreset;

}
