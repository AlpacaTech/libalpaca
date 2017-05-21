#pragma once
#include "drive.h"

namespace pid {
static const int DRIVE_MAX = 127;
static const int DRIVE_MIN = -127;
static const int INTEGRAL_LIMIT = 50;
extern float Kp;
extern float Ki;
extern float Kd;
extern unsigned int default_precision;
extern bool enabled[2];
void enable(void);
void disable(void);
void controller(void *none);
void init(void);
void stop(void);
void go(void);
void request(long l, long r);
void wait(long precision, unsigned long blockTime);
extern TaskHandle pidHandle;
}
