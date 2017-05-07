#pragma once
#include "pid.h"

namespace rerun {
  class frame {
  public:
    long left;
    long right;
  };
  void record();
  void stop();
  void replay();
  extern TaskHandle rerunHandle;
}
