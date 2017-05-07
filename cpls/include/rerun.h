#pragma once
#include "pid.h"

namespace rerun {
  struct frame {
    long left;
    long right;
  };
  void record();
  void stop();
  void replay();
  extern TaskHandle rerunHandle;
}
