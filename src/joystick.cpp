/*
 * @file joystick.cpp
 * @brief Source file that makes joystick stuff easier
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

#include "../include/joystick.hpp"

namespace Alpaca {
	Joystick::Joystick() {
		static unsigned char j;

		joyNum = ++j;
	}

	int Joystick::analog(unsigned char channel) {
		return joystickGetAnalog(joyNum, channel);
	} /* analog */

	bool Joystick::digital(unsigned char group, unsigned char button) {
		return joystickGetDigital(joyNum, group, button);
	} /* digital */
}   /* namespace Alpaca */
