#pragma once
#include "main.h"

namespace drive {
  class side {
  public:
    int topM;
    int midM;
    int lowM;
    void set(int power);
    sensors::quad* sensor;
  };
  side left;
  side right;
  void set(int lpower, int rpower);
}
