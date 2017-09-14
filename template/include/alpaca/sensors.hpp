/*
 * @file sensors.hpp
 * @brief Hardware abstraction for sensors on the robot, to make it easier to
 * access and interact with them.
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

#ifndef SENSORS_HPP
#define SENSORS_HPP

#include "../API.hpp"
#include <vector>

namespace Alpaca {
	/*
	 * The namespace containing all information, functions, objects, relating to
	 * sensors
	 */
	namespace sensors {
		/*
		 * Sensors enable the program to gather data about the surrounding
		 * environment
		 */
		class Sensor {
			protected:

				unsigned char ports[2];
				long _zero;
				bool _inverted;

			public:

				virtual void init();
				virtual long zero();
				virtual long zero(long val);
				virtual void reset();
				virtual bool inverted();
				virtual bool inverted(bool val);
				virtual long value();

				Sensor(unsigned char port,
				       bool          inverted = false,
				       unsigned char port2 = 0);
		}; /* class Sensor */

		/*
		 * Optical Quadrature encoders measure distance traveled in ticks, which can
		 * be converted to degrees by multiplying by 4. This is often useful on a
		 * lift or a drive to control position
		 */
		class Quad : public Sensor {
			protected:

				/*
				 * The encoder struct used by other member functions
				 */
				Encoder enc;

			public:

				void init();
				long value();
				using Sensor::Sensor;
		}; /* class Quad */

		/*
		 * Gyroscopes measure degrees rotated, and can be instrumental in doing
		 * complex maneuvers and even keeping as straight as possible
		 */
		class Gyroscope : public Sensor {
			public:

				/*
				 * Initialization funtion for the gyro, call in initialize()
				 */
				void init();

				/*
				 * Returns the current value of the gyro, relative to the zero
				 */
				long value();

				/*
				 * Create a new Gyroscope object
				 */
				Gyroscope(unsigned char port,
				          unsigned int  calibration = 0,
				          bool          inverted = false);

			protected:

				/*
				 * The calibration to be used in init
				 */
				unsigned int calibration;

				/*
				 * The Gyro struct to be used internally to interact with PROS
				 */
				Gyro gyro;
		}; /* class Gyroscope */

		/*
		 * Ultrasonics, also known as sonar sensors, sense the distance from the
		 * nearest object in front of it
		 */
		class Sonic : public Sensor {
			public:

				void init();
				long value();
				using Sensor::Sensor;

			protected:

				/*
				 * The Ultrasonic struct used to interact with PROS
				 */
				Ultrasonic sonic;
		}; /* class Sonic */

		/*
		 * Standard digital sensors have 2 states - on and off. This allows you to
		 * detect that state, and invert it if needed
		 */
		class Digital : public Sensor {
			public:

				/*
				 * Initializes the button. Call in initialize()
				 */
				void init(void);

				/*
				 * Returns true if the button is pressed
				 */
				long value(void);
				using Sensor::Sensor;
		}; /* class Digital */

		/*
		 * A list of all the sensors, such that Alpaca::init can be called in
		 * initialiaze to init all of the sensors
		 */
		extern std::vector<Sensor *> sensors;
	} /* namespace sensors */

	/*
	 * Initialize all of the sensors and stuff
	 */
	void init();
} /* namespace Alpaca */

#endif /* end of include guard: SENSORS_HPP */
