// joystick.hpp: Makes joystick stuff easier
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

#ifndef JOYSTICK_H
#define JOYSTICK_H
#include "../include/API.h"

/** The joystick class */
namespace joystick {
  /** A group of buttons on the joystick */
  typedef unsigned char Group;

  /** An analog channel on the joystick */
  typedef unsigned char Channel;

  /** A set of buttons within a group */
  typedef enum {
    Up    = JOY_UP,
    Down  = JOY_DOWN,
    Left  = JOY_LEFT,
    Right = JOY_RIGHT,
  } Button;

  /** Get the analog value of the specified channel */
  int analog(Channel channel);

  /** Returns whether or not a button in a group is pressed */
  bool digital(Group group, Button button);
}; // namespace joystick

#endif /* end of include guard: JOYSTICK_H */
