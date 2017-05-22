#pragma once
#include <API.h>

namespace sensors {
struct quad_t {
  Encoder enc;
  unsigned char ports[2];
  long zero;
  bool inverted;
  void reset(void);
  long value(void);
  float request;
};
extern quad_t left;
extern quad_t right;
void init(void);
void reset(void);
}
