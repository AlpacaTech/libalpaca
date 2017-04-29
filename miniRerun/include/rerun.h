#ifndef RERUN_H
#define RERUN_H
#include "main.h"

typedef struct {
  long left;
  long right;
} frame;

TaskHandle rerunHandle;

void record();

void recordStop();

void replay();

#endif
