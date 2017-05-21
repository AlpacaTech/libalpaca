#include <API.h>

struct motor {
  unsigned char port;
  char inverted;
  int power;
  unsigned long slewRate;
  float scale;
  unsigned long tlast;
  void set(int power);
};

namespace motors {
void set(motor _motor, int power);
int get(motor _motor);
motor init(unsigned char port, int inverted, long slewRate, float scale);
namespace slew {
extern motor list[11];
extern TaskHandle handle;
void init(void);
}
}
