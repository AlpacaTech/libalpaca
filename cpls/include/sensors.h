#pragma once
#include "main.h"

namespace sensors {
  class quad {
  public:
    Encoder self;
    unsigned char ports[2];
    long zero;
    int8_t inverted;
    void(*reset)();
    long(*value)();
    float request;
  };
  extern sensors::quad left();
  extern sensors::quad right();
  void init(void);
}
