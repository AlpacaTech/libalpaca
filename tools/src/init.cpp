// init.cpp: Handles the initialization of everything needed, ie. sensors, pid.
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

extern "C" {
void __libc_init_array();
}

void initializeIO() {
  __libc_init_array();
}

void initialize() {
  motors::slew::init();
  drive::init();
  sensors::init();
  pid::init();
}
