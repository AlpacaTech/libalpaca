#pragma once
#include <API.h>

struct motor_t {
  unsigned char port;
  char inverted;
  int power;
  float scale;
  float slewRate;
  unsigned long tlast;
  void set(int power);
};

namespace motors {
void set(motor_t motor, int power);
int get(motor_t motor);
motor_t init(unsigned char port, int inverted, float slewRate, float scale);
namespace slew {
static const unsigned char slewWait = 10;
extern motor_t list[11];
extern TaskHandle handle;
void init(void);
}
}
