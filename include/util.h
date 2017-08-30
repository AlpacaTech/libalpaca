/*
 * @file util.h
 * @brief General utilities that make coding easier
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

#ifndef UTIL_H
#define UTIL_H

/*
 * "Clips" a number between a high and low value
 *
 * @param	 input The number wanted clipped
 * @param	 high  Highest possible output
 * @param  low	 Lowest possible output
 *
 * @return value in between high and low
 */
#define clipNum(input, high, low) \
  input <= low ? low : (input >= high ? high : input)

/*
 * Determines whether a number is positive, negative, or 0.
 *
 * @param  input the number to be determined the sign of
 *
 * @return -1 if the number is negative,
 *					0 if the number is nuetral,
 *					1 if the number is positive.
 */
#define sgn(input) input == 0 ? 0 : (input > 0 ? 1 : -1)

#endif /* end of include guard: UTIL_H */
