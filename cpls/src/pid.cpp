#include "pid.h"

int sgn(float __x) {
  if (__x > 0) return 1;
  if (__x < 0) return -1;
  return 0;
}

namespace pid {
  float Kp = 0.8;
  float Ki = 0.04;
  float Kd = 0.4;

  bool enabled[2] = {true, true};
  TaskHandle pidHandle;

  void controller(void *none) {

    float pidCurrent[2];
    float pidError[2];
    float pidLastError[2] = {0, 0};
    float pidIntegral[2] = {0, 0};
    float pidDerivative[2];
    float pidPower[2];

    sensors::left.reset();
    sensors::right.reset();
    sensors::quad *sides[2] = {&sensors::left, &sensors::right};

    while (true) {
      printf("| %ld | %ld |\n", sensors::left.value(), sensors::right.value());
      for (size_t i = 0; i < 2; i++) {
        if (enabled[i]) {
          pidCurrent[i] = sides[i]->value();
          pidError[i] = sides[i]->request - pidCurrent[i];
          pidIntegral[i] = (Ki != 0 && abs(pidError[i]) < INTEGRAL_LIMIT) ? (pidIntegral[i] + pidError[i]) : 0;
          pidDerivative[i] = pidError[i] - pidLastError[i];
          pidLastError[i] = pidError[i];
          pidPower[i] = (Kp * pidError[i]) + (Ki * pidIntegral[i]) + (Kd * pidDerivative[i]);
          pidPower[i] = (pidPower[i] <= DRIVE_MIN) ? DRIVE_MIN : ((pidPower[i] >= DRIVE_MAX) ? DRIVE_MAX : pidPower[i]);
          (i == 0) ? drive::left.set(pidPower[i]) : drive::right.set(pidPower[i]);
        }
      }
      delay(25);
    }
  }

  void init(void) {
    pidHandle = taskCreate(controller, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
  }

  void stop(void) {
    taskSuspend(pidHandle);
  }

  void go(void) {
    taskResume(pidHandle);
  }

  void request(long l, long r) {
    sensors::left.request = l;
    sensors::right.request = r;
  }

  void wait(long precision) {
    while (sensors::left.value() > sensors::left.request + precision || sensors::left.value() < sensors::left.request - precision || sensors::right.value() > sensors::right.request + precision || sensors::right.value() < sensors::right.request - precision)
      delay(50);
  }
}
