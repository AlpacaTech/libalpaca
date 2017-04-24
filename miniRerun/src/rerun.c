#include "rerun.h"

bool isDriver(void) {
  return (isOnline() && !isAutonomous());
}

void toPos(long leftP, long rightP) {
  int leftpow, rightpow;
  if (left.value() > leftP) {
    leftpow = -127;
  } else if (left.value() < leftP) {
    leftpow = 127;
  } else {
    leftpow = 0;
  }

  if (right.value() > rightP) {
    rightpow = -127;
  } else if (right.value() < rightP) {
    rightpow = 127;
  } else {
    rightpow = 0;
  }
  driveSet(leftpow, rightpow);
}

void _record(void *nnone) {
  left.reset();
  right.reset();
  FILE *rerun;
  while (1) {
    if (isDriver()) {
      while ((rerun = fopen("rerun", "w")) == NULL)
        ;

      while (isDriver()) {
        fprintf(rerun, "%ld %ld\n", left.value(), right.value());
        printf("toPos(%ld, %ld);\n",  left.value(), right.value());
        delay(10);
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
  FILE *rerun;
  int leftR;
  int rightR;
  while ((rerun = fopen("rerun", "r")) == NULL)
    ;
  while (!isAutonomous())
    delay(5);

  fseek(rerun, 0, SEEK_SET);
  while (isAutonomous()) {
    leftR = fgetc(rerun);
    fseek(rerun, 2, SEEK_CUR);
    rightR = fgetc(rerun);
    fseek(rerun, 1, SEEK_CUR);
    toPos(leftR, rightR);
    delay(10);
  }
}
