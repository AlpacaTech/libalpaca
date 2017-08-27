/*
 * @file lift.cpp
 * @brief Allows easier abstraction with lift systems
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

#include "../include/lift.hpp"

namespace lift {
	void Side::set(int power) {
		Side::topM->set(power);
		Side::midM->set(power);
		Side::lowM->set(power);
	} // Side::set

	void lock(void) {
			set(lockN);
	} // lock

	void to(Position pos, int int_pos, int tolerance) {
		if (int_pos == -1) int_pos = pos;

		do {
			set((int_pos > sensor->value() + tolerance ||
					 int_pos < sensor->value() - tolerance)
					? (sensor->value() - int_pos) * 1.5
					: (sensor->value() - int_pos));
			delay(15);
		} while (int_pos > sensor->value() + tolerance ||
						 int_pos < sensor->value() - tolerance);
		lock();
	} // to

	void control(void) {
		int power = (joystick::digital(5, joystick::Up) * 127) +
								(joystick::digital(5, joystick::Down) * 127);

		power = (power == 0 && sensor->value() > threshold)
						? lockN
						: ((sensor->value() < threshold) ? 0 : power);
		set(power);
	} // control
}		// namespace lift
