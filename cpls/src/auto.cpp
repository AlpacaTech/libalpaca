#include "../include/main.h"

void autonomous() {
  sensors::reset();
  if (rerun::enabled)
    rerun::replay();
  drive::inches(12);
}
