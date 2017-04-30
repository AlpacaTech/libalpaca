#include "main.h"


extern "C" {
  void __libc_init_array();
}

void initializeIO() {
  __libc_init_array();
}

void initialize() {
}
