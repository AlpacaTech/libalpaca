#include "rerun.h"

bool isDriver(void) {return (isOnline() && !isAutonomous());}

void toPos(long leftP, long rightP) {
  if (left.value() > leftP) {
    motorSet(LEFT, -127);
  } else if (left.value() < leftP) {
    motorSet(LEFT, 127);
  } else {
    motorStop(LEFT);
  }

  if (right.value() > rightP) {
    motorSet(RIGHT, -127);
  } else if (right.value() < rightP) {
    motorSet(RIGHT, 127);
  } else {
    motorStop(RIGHT);
  }
}

void _record(void *nnone) {
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
  }
}
