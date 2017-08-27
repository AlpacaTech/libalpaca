/*
 * @file pid.hpp
 * @brief Easy use and tuning of pid for different subsystems
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

#ifndef PID_HPP
#define PID_HPP

#include "lift.hpp"
#include "motors.hpp"
#include <list>

namespace Alpaca {
	/*
	 * Class for motors that are slave to a sensor
	 */
	struct System {
		sensors::AnalogSensor *sensor;
		std::list<Motor>      *motors;
	}; /* class System */

	/*
	 * Consists of pid, and all subcomponents, etc
	 */
	class Pid {
		public:

			class Settings {
				public:

					Settings(float        Kp,
					         float        Ki,
					         float        Kd,
					         System       system,
					         int          max,
					         int          min,
					         int          iLimit,
					         unsigned int precision);

					friend Pid;

				protected:

					/*
					 * Maximum value to be assigned to the controlled system
					 */
					int max = 127;

					/*
					 * Minimum value to be assigned to the controlled system
					 */
					int min = -127;

					/*
					 * Limit for the integral value
					 */
					int iLimit = 50;

					/*
					 * p value
					 */
					float Kp;

					/*
					 * i value
					 */
					float Ki;

					/*
					 * d value
					 */
					float Kd;

					/*
					 * Precision for waiting on pid to reach value
					 */
					unsigned int precision;

					/*
					 * The system the pid controls
					 */
					System system;
			};

			Pid(float        Kp,
			    float        Ki,
			    float        Kd,
			    long         target,
			    System       system,
			    int          max = 127,
			    int          min = -127,
			    int          iLimit = 50,
			    unsigned int precision = 15);

			Pid(Settings *settings,
			    long      target);

		private:

			void loop();

			Settings *settings;
			long target;
	}; /* class Pid */
} /* namespace Alpaca */
#endif /* end of include guard: PID_HPP */
