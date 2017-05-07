#include "main.h"

bool isDriver(void) {
  return (isOnline() && !isAutonomous());
}

namespace rerun {
  TaskHandle rerunHandle;

  void toPos(frame _frame) {
    pid::request(_frame.left, _frame.right);
  }

  void _record(void *none) {
    sensors::reset();
    PROS_FILE *rerun;
    frame now;
    while (1) {
      if (isDriver()) {
        while ((rerun = fopen("rerun", "w")) == NULL)
          ;

        while (isDriver()) {
          now.left = sensors::left.request;
          now.right = sensors::right.request;
          fwrite(&now, sizeof(now), 1, rerun);
          delay(50);
        }
        fclose(rerun);
      }
    }
  }

  void record() {
    rerunHandle = taskCreate(_record, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  }

  void _recordStop(void *none) {
    taskDelete(rerunHandle);
  }

  void stop() {
    taskCreate(_recordStop, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  }

  void replay() {
    sensors::reset();
    pid::enabled[0] = true;
    pid::enabled[1] = true;
    frame to;
    PROS_FILE *rerun;
    if ((rerun = fopen("rerun", "r")) == NULL) {
      return;
    }

    while (isAutonomous()) {
      if (fread((void*)&to, sizeof(to), 1, rerun) < sizeof(to)) {
        return;
      }
      toPos(to);
      delay(50);
    }
  }
}
