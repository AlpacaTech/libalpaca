#include <API.h>

struct motor {
  unsigned char port;
  char inverted;
  int power;
  unsigned long slewRate;
  float scale;
  unsigned long tlast;
  void set(int power);
  motor();
};

namespace motors {
  void set(motor *_motor, int power);
  int get(motor _motor);
  motor* init(unsigned char port, char inverted, long slewRate, float scale);
  extern motor list[11];
  namespace slew {
    void init(void);
    extern TaskHandle slewHandle;
  }
}
