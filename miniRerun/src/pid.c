#include "pid.h"

float pidRequestedValue[2];

int sgn(float __x) {
  if (__x > 0) return 1;
  if (__x < 0) return -1;
  return 0;
}

void pidController(void *none) {
  pid_Kp = 0.8;
  pid_Ki = 0.04;
  pid_Kd = 0.4;
  pidEnabled = true;

  float pidCurrent[2];
  float pidError[2];
  float pidLastError[2] = {0, 0};
  float pidIntegral[2] = {0, 0};
  float pidDerivative[2];
  float pidPower[2];

  left.reset();
  right.reset();
  quad *sides[2] = {&left, &right};
  void(*sideSet[2])(int) = {&leftSet, &rightSet};

  while (true) {
    printf("| %ld | %ld |\n", left.value(), right.value());
    if (pidEnabled) {
      for (size_t i = 0; i < 2; i++) {
        pidCurrent[i] = sides[i]->value();
        pidError[i] = pidRequestedValue[i] - pidCurrent[i];
        pidIntegral[i] = (pid_Ki != 0 && abs(pidError[i]) < PID_INTEGRAL_LIMIT) ? (pidIntegral[i] + pidError[i]) : 0;
        pidDerivative[i] = pidError[i] - pidLastError[i];
        pidLastError[i] = pidError[i];
        pidPower[i] = (pid_Kp * pidError[i]) + (pid_Ki * pidIntegral[i]) + (pid_Kd * pidDerivative[i]);
        pidPower[i] = (pidPower[i] <= PID_DRIVE_MIN) ? PID_DRIVE_MIN : ((pidPower[i] >= PID_DRIVE_MAX) ? PID_DRIVE_MAX : pidPower[i]);
        sideSet[i](pidPower[i]);
      }
      delay(25);
    }
  }
}

void autoPid() {
  pidEnabled = (isAutonomous() && isEnabled());
}
