// rerun.cpp: Source file for the components of rerun
// Copyright (C) 2017 Ethan Wellsi
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

#include "../include/main.h"

bool isDriver(void) { return (isOnline() && !isAutonomous()); }

namespace rerun {
bool enabled;
TaskHandle rerunHandle;

frame_t::frame_t(long _left, long _right) {
  left  = _left;
  right = _right;
}

void toPos(frame_t frame) { pid::request(frame.left, frame.right); }

void _record(void* none) {
  if (enabled) {
    PROS_FILE* store;
    sensors::reset();
    frame_t now(0, 0);
    while (1) {
      if (isDriver()) {
        while ((store = fopen("rerun", "w")) == NULL)
          ;

        while (isDriver()) {
          now = frame_t(sensors::left.request, sensors::right.request);
          fwrite(&now, sizeof(now), 1, store);
          delay(50);
        }
        fclose(store);
      }
    }
  }
  free(none);
}

void record() {
  rerunHandle =
      taskCreate(_record, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void _recordStop(void* none) {
  taskDelete(rerunHandle);
  free(none);
}

void stop() {
  taskCreate(_recordStop, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void replay() {
  if (enabled) {
    PROS_FILE* store;
    sensors::reset();
    pid::enable();
    frame_t to(0, 0);
    if ((store = fopen("rerun", "r")) == NULL) {
      return;
    }

    while (isAutonomous()) {
      if (fread((void*)&to, sizeof(to), 1, store) < sizeof(to)) {
        return;
      }
      toPos(to);
      delay(50);
    }
    fclose(store);
  }
}
}
