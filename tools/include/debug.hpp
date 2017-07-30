// debug.hpp: Header file for performing debugging tasks
// Copyright (C) 2017 Ethan Wells
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "pid.hpp"

/** Contains debugging funtions, etc */
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

  /** Debug the Cortex if something goes wrong */
  void debug(void);
} // namespace debug

#endif /* end of include guard: DEBUG_HPP */
