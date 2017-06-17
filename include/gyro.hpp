// gyro.hpp: Gyro utilities that provide ease of access to the robot's rotation
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

#pragma once
#include "pid.hpp"

namespace gyro {
  class drive {
    public:
      sensors::gyro_t* gyro;
      int heading;

  };

  /** TaskHandle for the gyro heading task */
  extern TaskHandle handle;
} // namespace gyro
