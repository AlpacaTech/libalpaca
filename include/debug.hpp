#include "rerun.hpp"

namespace debug {
extern uint32_t fault;

template <class T>
static inline T unserialize(PROS_FILE* stream) {
  alignas(alignof(T)) char buf[sizeof(T)];
  size_t nread = fread((void*)buf, sizeof(T), 1, stream);
  if (nread < sizeof(T)) {
    return T();
  }
  T* out = (T*)buf;
  return *out;
}

void debug(void);
}
