#include "main.h"

namespace sensors {

quad left;
quad right;

void quad::reset(void) { encoderReset(quad::enc); }

long quad::value(void) { return (encoderGet(quad::enc) - quad::zero); }

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
