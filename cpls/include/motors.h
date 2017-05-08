#include <API.h>

struct motor {
  unsigned char port;
  char inverted;
  int power;
  long slewRate;
  float scale;
  void set(int power);
};

namespace motors {
  void set(motor _motor, int power);
  int get(motor _motor);
  motor init(unsigned char port, int inverted, long slewRate, float scale);
}
