#include "../include/main.h"

bool isDriver(void) { return (isOnline() && !isAutonomous()); }

namespace rerun {
bool enabled;
TaskHandle rerunHandle;

void toPos(frame_t frame) { pid::request(frame.left, frame.right); }

void _record(void* none) {
  if (enabled) {
    PROS_FILE* store;
    sensors::reset();
    frame_t now;
    while (1) {
      if (isDriver()) {
        while ((store = fopen("rerun", "w")) == NULL)
          ;

        while (isDriver()) {
          now.left  = sensors::left.request;
          now.right = sensors::right.request;
          fwrite(&now, sizeof(now), 1, store);
          delay(50);
        }
        fclose(store);
      }
    }
  }
}

void record() {
  rerunHandle =
      taskCreate(_record, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void _recordStop(void* none) { taskDelete(rerunHandle); }

void stop() {
  taskCreate(_recordStop, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void replay() {
  if (enabled) {
    PROS_FILE* store;
    sensors::reset();
    pid::enabled[0] = true;
    pid::enabled[1] = true;
    frame_t to;
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
