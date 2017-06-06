// sensors.hpp: Header file for hardware abstraction of sensors
// Copyright (C) 2017 Ethan Wells
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#pragma once
#include "API.h"

namespace sensors {
struct quad_t {
  Encoder enc;
  unsigned char ports[2];
  long zero;
  bool inverted;
  void reset(void);
  long value(void);
  float request;
  void init(void);
  quad_t(unsigned char port1, unsigned char port2, bool _inverted);
};
class gyro_t {
  int calibration;

 public:
  Gyro gyro;
  unsigned char port;
  long zero;
  void reset(void);
  long value(void);
  float request;
  void init(void);
  gyro_t(unsigned char _port, unsigned int _calibration);
};
struct pot_t {
  unsigned char port;
  long zero;
  bool inverted;
  void reset(void);
  long value(void);
  float request;
  void init(void);
  pot_t(unsigned char _port, bool _inverted);
};
struct sonic_t {
  Ultrasonic sonic;
  unsigned char ports[2];
  long value(void);
  void init(void);
  sonic_t(unsigned char port1, unsigned char port2);
};
struct button_t {
  unsigned char port;
  bool inverted;
  bool value(void);
  void init(void);
  button_t(unsigned char _port, bool _inverted);
};
void init(void);
void reset(void);

extern quad_t left;
extern quad_t right;
}
