#ifndef PID_H
#define PID_H
#include "main.h"

#define PID_DRIVE_MAX 127
#define PID_DRIVE_MIN (-127)

#define PID_INTEGRAL_LIMIT 50

float pid_Kp;
float pid_Ki;
float pid_Kd;

static float pidRequestedValue[2];
bool pidEnabled;

void pidController(void *none);
TaskHandle pidControllerHandle;

#endif
