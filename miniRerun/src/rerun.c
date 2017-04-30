#include "main.h"

extern float pidRequestedValue[2];

bool isDriver(void) {
  return (isOnline() && !isAutonomous());
}

void toPos(frame _frame) {
  pidRequestedValue[0] = _frame.left;
  pidRequestedValue[1] = _frame.right;
}

void _record(void *none) {
  left.reset();
  right.reset();
  FILE *rerun;
  frame now;
  while (1) {
    if (isDriver()) {
      while ((rerun = fopen("rerun", "w")) == NULL)
        ;

      while (isDriver()) {
        now.left = pidRequestedValue[0];
        now.right = pidRequestedValue[1];
        fwrite(&now, sizeof(now), 1, rerun);
        //printf("toPos(%ld, %ld);\n",  left.value(), right.value());
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

void recordStop() {
  taskCreate(_recordStop, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}

void replay() {
  left.reset();
  right.reset();
  frame to;
  FILE *rerun;
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
