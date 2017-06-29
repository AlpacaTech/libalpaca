// gyro.cpp: Gyro utilities that provide ease of access to the robot's rotation
// and manipulation of this rotation
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

#include "../include/main.h"

namespace gyro {
  void drive::task(void* none) {
    float change[2] = {0};
    int tolerance = 2;
    while (on) {
      changer = (abs(gyro->value() - iHeading) - tolerance) * 15;
      if (rGyros() - startp > tolerance) {
        lpower = power - changer;
        rpower = power + changer;
      } else if (rGyros() - startp < -tolerance) {
        lpower = power + changer;
        change[1] -= changer;
      }
      pid::request(change[0], change[1]);
      delay(50);
    }
    free(none);
  }

  void drive::off(void) {
    on = false;
  }

  drive::drive(int _heading, float _urgency, bool absolute,
               sensors::gyro_t* _gyro) {
    heading  = _heading;
    urgency  = _urgency;
    gyro     = _gyro;
    on       = true;
    iHeading = absolute ? heading : heading + gyro->value();
  }

} // namespace gyro
