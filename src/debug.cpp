/*
 * @file debug.cpp
 * @brief Allows easier location of segfaults in code
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

#include "../include/alpaca/debug.hpp"

namespace Alpaca {
	namespace debug {
		unsigned long fault = 0;
		void debug(void) {
			PROS_FILE *fd = fopen("FAULT_PC", "r");

			if (fd) {
				fault = unserialize<uint32_t>(fd);

				if (!fault) {
					fault = 0xFFFFFFFF;
				}
				fclose(fd);
			}
			printf("%lu", fault);
		} /* debug */
	}   /* namespace debug */
}     /* namespace Alpaca */
