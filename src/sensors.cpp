#include "../include/main.h"

namespace sensors {

quad_t left(1, 2, false);
quad_t right(3, 4, false);

quad_t::quad_t(unsigned char port1, unsigned char port2, bool _inverted) {
  ports[0] = port1;
  ports[1] = port2;
  inverted = _inverted;
  zero     = 0;
  request  = 0;
}
void quad_t::init(void) {
  enc = encoderInit(quad_t::ports[0], quad_t::ports[1], quad_t::inverted);
}
long quad_t::value(void) { return (encoderGet(enc) - zero); }
void quad_t::reset(void) {
  zero    = encoderGet(enc);
  request = 0;
}

gyro_t::gyro_t(unsigned char _port, unsigned int _calibration) {
  port        = _port;
  calibration = _calibration;
  zero        = 0;
  request     = 0;
}
void gyro_t::init(void) { gyro_t::gyro = gyroInit(port, calibration); }
long gyro_t::value(void) { return (gyroGet(gyro_t::gyro) - zero); }
void gyro_t::reset(void) {
  zero    = gyroGet(gyro_t::gyro);
  request = 0;
}

pot_t::pot_t(unsigned char _port, bool _inverted) {
  port     = _port;
  inverted = _inverted;
  zero     = 0;
  request  = 0;
}
void pot_t::init(void) { analogCalibrate(port); }
long pot_t::value(void) {
  return ((analogReadCalibrated(port) - zero) * ((inverted) ? -1 : 1));
}
void pot_t::reset(void) {
  zero    = analogReadCalibrated(port);
  request = 0;
}

sonic_t::sonic_t(unsigned char port1, unsigned char port2) {
  ports[0] = port1;
  ports[1] = port2;
}
void sonic_t::init(void) {
  sonic = ultrasonicInit(sonic_t::ports[0], sonic_t::ports[1]);
}
long sonic_t::value(void) { return ultrasonicGet(sonic); }

button_t::button_t(unsigned char _port, bool _inverted) {
  port     = _port;
  inverted = _inverted;
}
void button_t::init(void) { pinMode(port, INPUT); }
bool button_t::value(void) {
  return (digitalRead(port)) ? ((inverted) ? false : true)
                             : ((inverted) ? true : false);
}

void init(void) {
  left.init();
  right.init();
}

void reset(void) {
  left.reset();
  right.reset();
}
}
