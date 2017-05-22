#include "main.h"

namespace sensors {

quad_t left;
quad_t right;

void quad_t::reset(void) { encoderReset(quad_t::enc); }

long quad_t::value(void) { return (encoderGet(quad_t::enc) - quad_t::zero); }

void init(void) {
  left.ports[0] = 1;
  left.ports[1] = 2;
  right.ports[0] = 3;
  right.ports[1] = 4;
  left.inverted = false;
  right.inverted = false;
  left.enc = encoderInit(left.ports[0], left.ports[1], left.inverted);
  right.enc = encoderInit(right.ports[0], right.ports[1], right.inverted);
  left.zero = 0;
  right.zero = 0;
}

void reset(void) {
  left.reset();
  right.reset();
  left.request = 0;
  right.request = 0;
}
}
