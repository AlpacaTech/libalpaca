#include "debug.hpp"

namespace debug {
uint32_t fault = 0;
void debug(void) {
  PROS_FILE *fd = fopen("FAULT_PC", "r");
  if (fd) {
    fault = unserialize<uint32_t>(fd);
    if (!fault) {
      fault = 0xFFFFFFFF;
    }
    fclose(fd);
  }
  printf("%ld", fault);
}
}
