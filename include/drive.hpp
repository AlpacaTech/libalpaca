// drive.hpp: Header file for utilities relating to the drive
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
#include "motors.hpp"
#include "sensors.hpp"

namespace drive {
struct side_t {
  motor_t topM;
  motor_t midM;
  motor_t lowM;
  void set(int power);
  sensors::quad_t* sensor;
};
extern double inch;
extern side_t left;
extern side_t right;

/** Set both sides of the drive at their requested powers */
void set(int lpower, int rpower);

/** Initialize the drive system */
void init(void);

/** Drive a specific number of inches */
void inches(long inches);

/** Tank control that should be used in a while loop */
void tank(void);
namespace accel {
extern int x;
extern int y;
extern int prevX;
extern int prevY;

/** Tilt control using the josytick accelerometer. Should be used in a while
 * loop */
void drive(void);
}
}
