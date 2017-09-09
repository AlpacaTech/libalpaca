/*
 * @file motors.hpp
 * @brief Hardware abstraction on the motors of the robot for easier
 * organization and use of motors and their properties, as well as slewing.
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

#ifndef MOTORS_HPP
#define MOTORS_HPP

#include "../API.hpp"
#include "util.hpp"

namespace Alpaca {
	/*
	 * Class containing the slew data for a motor
	 */
	class MotorData {
		public:

			/*
			 * The requested power value
			 */
			int request;

			/*
			 * The slew rate
			 */
			int rate;

			/*
			 * The last update time
			 */
			unsigned long lastTime;

			/*
			 * The last power value
			 */
			int lastPower;

			/*
			 * Whether or not slewing is enabled
			 */
			bool on;
	}; /* class MotorData */

	/*
	 * Class for motor objects
	 */
	class Motor {
		public:

			/*
			 * Set the motor to the specified power
			 */
			void set(int power);

			/*
			 * The last update time of the motor. Is managed by the slew task, so it
			 * shouldn't need to be changed
			 */
			unsigned long tlast;

			/*
			 * Port the motor is plugged in to
			 */
			unsigned char port;

			/*
			 * The invertation of the motor, should be 1 or -1
			 */
			char inverted;

			/*
			 * The requested power value of the motor
			 */
			int power;

			/*
			 * A multiplier for setting the motor values
			 */
			float scale;

			/*
			 * The data for slewing specific to this motor
			 */
			MotorData *slew;
	}; /* class Motor*/

	/*
	 * Namespace relating to the motors and setting them, initializing them,
	 * slewing, etc
	 */
	namespace motors {
		/*
		 * Sets the motor to the power
		 */
		void set(Motor motor,
		         int   power);

		/*
		 * Returns an initialized Motorobject with the specified parameters, and
		 * adds a duplicate of the motor to the motor list for slewing
		 */
		Motor init(char  port = -1,
		           int   inverted = 1,
		           bool  slew = false,
		           int   slewRate = 0,
		           float scale = 0.0);

		/*
		 * Namespace relating to slewing the motors to save the gears and the PTCs
		 */
		namespace slew {
			/*
			 * The wait time between each iteration of setting all of the motors
			 */
			static const unsigned char slewWait = 10;

			/*
			 * The list of motors, as added to in motors::init()
			 */
			extern MotorData list[10];

			/*
			 * The TaskHandle for handling the slewing task
			 */
			extern TaskHandle handle;

			/*
			 * Initialization function for slewing. Call in initialize()
			 */
			void init(void);
		} /* namespace slew */
	}   /* namespace motors */
}     /* namespace Alpaca */

#endif /* end of include guard: MOTORS_HPP */
