#ifndef PID_H
#define PID_H
#include "main.h"

#define PID_DRIVE_MAX 127
#define PID_DRIVE_MIN (-127)

#define PID_INTEGRAL_LIMIT 50

float pid_Kp;
float pid_Ki;
float pid_Kd;

bool pidEnabled;

TaskHandle pidControllerHandle;
TaskHandle autoPidHandle;

void pidController(void *none);
void autoPid();

#endif
