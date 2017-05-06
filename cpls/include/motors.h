#include <API.h>

class motor {
public:
  unsigned char port;
  bool inverted;
  long slewRate;
};

namespace motors {
  void set(motor _motor, int power);
  int get(motor _motor);
  void init(motor* _motor, unsigned char port, bool inverted, long slewRate);
}
