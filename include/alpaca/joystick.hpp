/*
 * @file joystick.hpp
 * @brief Basically an alias of the joystickGet functions, but can be easier and
 * simpler to use
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

#ifndef JOYSTICK_H
#define JOYSTICK_H
#include "../API.hpp"

namespace Alpaca {
	/*
	 * A simple interaction with VEX Joysticks
	 */
	class Joystick {
		public:

			static const unsigned char Up    = JOY_UP;
			static const unsigned char Down  = JOY_DOWN;
			static const unsigned char Left  = JOY_LEFT;
			static const unsigned char Right = JOY_RIGHT;

			/*
			 * Get the analog value of the specified channel
			 */
			int  analog(unsigned char channel);

			/*
			 * Returns whether or not a button in a group is pressed
			 */
			bool digital(unsigned char group,
									unsigned char button);

			/*
			 * Automatically increments the joystick number with each joystick created
			 */
			Joystick();

		private:

			/*
			 * The joystick number
			 */
		unsigned char joyNum;
	}; /* class joystick */
}    /* namespace Alpaca */

#endif /* end of include guard: JOYSTICK_H */
