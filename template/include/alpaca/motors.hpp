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
	 * Class for motor objects
	 */
	class Motor {
		private:

			static inline float default_scale(int p) {
				return (float)(p);
			} /* default_scale */

		public:

			/*
			 * Class containing the slew data for a motor
			 */
			struct MotorData {
				/*
				 * The requested power value
				 */
				int request;

				/*
				 * The slew rate
				 */
				float rate;

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
			 * Set the motor to the specified power
			 */
			void set(int power);

			/*
			 * Initialize the motor
			 */

			Motor(char  inverted = 1,
			      char  motorPort = -1,
			      bool  isSlew = false,
			      float slewRate = 0,
			      float(*scale)(int) = & default_scale);

		private:

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
			float (*scale)(int);

			/*
			 * The data for slewing specific to this motor
			 */
			MotorData *slew;
	}; /* class Motor */

	namespace slew {
		/*
		 * The wait time between each iteration of setting all of the motors
		 */
		static const unsigned char slewWait = 10;

		/*
		 * The list of motors, as added to in motors::init()
		 */
		extern Motor::MotorData list[10];

		/*
		 * The TaskHandle for handling the slewing task
		 */
		extern TaskHandle handle;

		/*
		 * Initialization function for slewing. Call in initialize()
		 */
		void init(void);
	} /* namespace slew */
}   /* namespace Alpaca */

#endif /* end of include guard: MOTORS_HPP */
