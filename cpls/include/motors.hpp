#include <API.h>

struct motor_t {
  unsigned char port;
  char inverted;
  int power;
  float scale;
  unsigned long slewRate;
  unsigned long tlast;
  void set(int power);
};

namespace motors {
void set(motor_t motor, int power);
int get(motor_t motor);
motor_t init(unsigned char port, int inverted, long slewRate, float scale);
namespace slew {
extern motor_t list[11];
extern TaskHandle handle;
void init(void);
}
}
