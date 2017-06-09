// rerun.hpp: Header file for the components of rerun
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

/** Contains components of rerun */
namespace rerun {
/** Class of a rerun frame. Rerun frames consist of the pid requested value for
 * the left and right sides of the drive */
struct frame_t {
  /** Left pid requested value for the frame */
  long left;
  /** Right pid requested value for the frame */
  long right;
  /** Constructor for a rerun frame */
  frame_t(long left, long right);
};

/** Begin recording rerun into memory */
void record();

/** Stop recording rerun into memory */
void stop();

/** Replay the recorded rerun */
void replay();
/** Whether or not rerun is enabled */
extern bool enabled;
/** The TaskHandle for the rerun task */
extern TaskHandle rerunHandle;
}
