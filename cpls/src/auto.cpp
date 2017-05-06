#include "main.h"

void autonomous() {
  sensors::reset();
  pid::request(300, 300);
  pid::wait(10);
}
