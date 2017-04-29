#include "pid.h"

void pidController(void *none) {
  pid_Kp = 2.0;
  pid_Ki = 0.04;
  pid_Kd = 0.0;
  pidEnabled = true;

  float pidSensorCurrentValue[2];
  float pidError[2];
  float pidLastError[2] = {0, 0};
  float pidIntegral[2] = {0, 0};
  float pidDerivative[2];
  float pidDrive[2];

  left.reset();
  right.reset();
  quad *sides[2] = {&left, &right};

  while (true) {
    if (pidEnabled) {
      for (size_t i = 0; i < 2; i++) {
        pidSensorCurrentValue[i] = sides[i]->value();
        pidError[i] = pidSensorCurrentValue[i] - pidRequestedValue[i];
        if (pid_Ki != 0) {
          if (abs(pidError[i]) < PID_INTEGRAL_LIMIT)
            pidIntegral[i] = pidIntegral[i] + pidError[i];
          else
            pidIntegral[i] = 0;
        } else
          pidIntegral[i] = 0;
        pidDerivative[i] = pidError[i] - pidLastError[i];
        pidLastError[i] = pidError[i];
        pidDrive[i] = (pid_Kp * pidError[i]) + (pid_Ki * pidIntegral[i]) +
                      (pid_Kd * pidDerivative[i]);
        if (pidDrive[i] > PID_DRIVE_MAX)
          pidDrive[i] = PID_DRIVE_MAX;
        if (pidDrive[i] < PID_DRIVE_MIN)
          pidDrive[i] = PID_DRIVE_MIN;
        if (sides[i] == &left) {
          leftSet(pidDrive[i]);
        } else {
          rightSet(pidDrive[i]);
        }
      }
      delay(25);
    }
  }
}
