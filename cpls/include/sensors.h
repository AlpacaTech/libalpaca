#pragma once
#include "API.h"

namespace sensors {
  class quad {
  public:
    Encoder enc;
    unsigned char ports[2];
    long zero;
    bool inverted;
    void reset(void);
    long value(void);
    float request;
  };
  extern quad left;
  extern quad right;
  void init(void);
  void reset(void);
}
