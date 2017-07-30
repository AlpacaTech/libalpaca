// opcontrol.cpp: Handles the interaction and procedure of opcontrol mode
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
bool tank     = true;
bool wpressed = false;

void operatorControl() {
  sensors::reset();

  while (isEnabled()) {
    debug::debug();
    if (tank) {
      drive::tank();
    } else {
      drive::accel::drive();
    }
    if (!wpressed && joystick::digital(7, joystick::Down)) {
      tank = !tank;
    } else {
      wpressed = joystick::digital(7, joystick::Down);
    }
    lift::control();
    delay(50);
  }
}
