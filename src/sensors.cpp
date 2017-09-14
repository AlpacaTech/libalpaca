/*
 * @file sensors.cpp
 * @brief Hardware abstraction of sensors
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

#include "../include/main.hpp"

namespace Alpaca {
	namespace sensors {
    std::vector<Sensor*> sensors;
		void Sensor::init() {
			analogCalibrate(ports[0]);
		} /* init */

		long Sensor::zero() {
			return _zero;
		} /* zero */

		long Sensor::zero(long val) {
			_zero = val;
			return _zero;
		} /* zero */

		void Sensor::reset() {
			_zero = value();
		} /* reset */

		bool Sensor::inverted() {
			return _inverted;
		} /* inverted */

		bool Sensor::inverted(bool val) {
			return _inverted = val;
		} /* inverted */

		long Sensor::value() {
			return analogRead(ports[0]) - _zero;
		} /* value */

		Sensor::Sensor(unsigned char port,
		               bool          inverted,
		               unsigned char port2) : _inverted(inverted) {
			_zero    = 0;
			ports[0] = port;
			ports[1] = port2;
			sensors.push_back(this);
		}

		void Quad::init(void) {
			enc = encoderInit(ports[0], ports[1], _inverted);
		} /* Quad::init */

		long Quad::value(void) {
			return encoderGet(enc) - _zero;
		} /* Quad::value */

		Gyroscope::Gyroscope(unsigned char port,
		                     unsigned int  calibration,
		                     bool          inverted) : Sensor(port, inverted),
			                                             calibration(calibration) {
			sensors.push_back(this);
		}

		void Gyroscope::init(void) {
			Gyroscope::gyro = gyroInit(ports[0], calibration);
		} /* Gyroscope::init */

		long Gyroscope::value(void) {
			return gyroGet(Gyroscope::gyro) - _zero;
		} /* Gyroscope::value */

		void Sonic::init(void) {
			sonic = ultrasonicInit(Sonic::ports[0], Sonic::ports[1]);
		} /* Sonic::init */

		void Digital::init(void) {
			pinMode(ports[0], INPUT);
		} /* Button::init */

		long Digital::value(void) {
			return (long)((_inverted) ? digitalRead(ports[0]) : !digitalRead(ports[0]));
		} /* Button::value */
	}   /* namespace sensors */

	void init() {
		for (auto s : sensors::sensors) {
			s->init();
		}
	} /* init */
}     /* namespace Alpaca */
