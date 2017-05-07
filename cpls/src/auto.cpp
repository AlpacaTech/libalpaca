#include "main.h"

void autonomous() {
  sensors::reset();
  pid::request(300, 300);
  pid::wait(10);

  sensors::reset();
  delay(5000);

  rerun::replay();
}
