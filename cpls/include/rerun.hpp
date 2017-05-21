#pragma once
#include "pid.hpp"

namespace rerun {
struct frame_t {
  long left;
  long right;
};
void record();
void stop();
void replay();
extern TaskHandle rerunHandle;
}
