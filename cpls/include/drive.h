#pragma once
#include "sensors.h"

namespace drive {
  class side {
    public:
      int topM;
      int midM;
      int lowM;
      void set(int power);
      sensors::quad* sensor;
    };
  extern side left;
  extern side right;
  void set(int lpower, int rpower);
}
