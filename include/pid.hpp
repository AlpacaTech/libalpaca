// pid.hpp: Header file for the pid controller and all of it's assets
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
#include "drive.hpp"

namespace pid {
static const int DRIVE_MAX      = 127;
static const int DRIVE_MIN      = -127;
static const int INTEGRAL_LIMIT = 50;
extern float Kp;
extern float Ki;
extern float Kd;
extern unsigned int default_precision;
extern bool enabled[2];
void enable(void);
void disable(void);
void controller(void* none);
void init(void);
void stop(void);
void go(void);
void request(long l, long r);
void wait(long precision, unsigned long blockTime);
extern TaskHandle pidHandle;
}
