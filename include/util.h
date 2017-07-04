// util.h: General utilities
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

#ifndef UTIL_H
#define UTIL_H

/** Clips iInput to a high of iHigh and a low of iLow - good for keeping a
 * number to a maximum/minimum value */
#define clipNum(iInput, iHigh, iLow) \
  iInput <= iLow ? iLow : (iInput >= iHigh ? iHigh : iInput)

#endif /* end of include guard: UTIL_H */
