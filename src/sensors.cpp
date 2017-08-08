/*
 * @file sensors.cpp
 * @brief Hardware abstraction of sensors
 *
 * Copyright (C) 2017 Contributors to Alpaca Tech
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../include/main.h"

namespace sensors {
  quad_t::quad_t(unsigned char port1, unsigned char port2, bool inverted)
    : inverted(inverted) {
    ports[0] = port1;
    ports[1] = port2;
    zero     = 0;
    request  = 0;
  }

  void quad_t:: init(void) {
    enc = encoderInit(quad_t::ports[0], quad_t::ports[1], quad_t::inverted);
  } // quad_t::init

  long quad_t:: value(void) {
    return encoderGet(enc) - zero;
  } // quad_t::value

  void quad_t:: reset(void) {
    zero    = encoderGet(enc);
    request = 0;
  } // quad_t::reset

  gyro_t::gyro_t(unsigned char port, unsigned int calibration)
    : port(port), calibration(calibration) {
    zero    = 0;
    request = 0;
  }

  void gyro_t:: init(void) {
    gyro_t::gyro = gyroInit(port, calibration);
  } // gyro_t::init

  long gyro_t:: value(void) {
    return gyroGet(gyro_t::gyro) - zero;
  } // gyro_t::value

  void gyro_t:: reset(void) {
    zero    = gyroGet(gyro_t::gyro);
    request = 0;
  } // gyro_t::reset

  pot_t::pot_t(unsigned char port, bool inverted)
    : port(port), inverted(inverted) {
    zero    = 0;
    request = 0;
  }

  void pot_t:: init(void) {
    analogCalibrate(port);
  } // pot_t::init

  long pot_t:: value(void) {
    return (analogReadCalibrated(port) - zero) * ((inverted) ? -1 : 1);
  } // pot_t::value

  void pot_t:: reset(void) {
    zero    = analogReadCalibrated(port);
    request = 0;
  } // pot_t::reset

  sonic_t::sonic_t(unsigned char port1, unsigned char port2) {
    ports[0] = port1;
    ports[1] = port2;
  }

  void sonic_t:: init(void) {
    sonic = ultrasonicInit(sonic_t::ports[0], sonic_t::ports[1]);
  } // sonic_t::init

  long sonic_t:: value(void) {
    return ultrasonicGet(sonic);
  } // sonic_t::value

  button_t::button_t(unsigned char port, bool inverted)
    : port(port), inverted(inverted) {}

  void button_t:: init(void) {
    pinMode(port, INPUT);
  } // button_t::init

  bool button_t:: value(void) {
    return (digitalRead(port)) ? ((inverted) ? false : true)
           : ((inverted) ? true : false);
  } // button_t::value

  void reset(void) {
    left.reset();
    right.reset();
  } // reset
}   // namespace sensors
