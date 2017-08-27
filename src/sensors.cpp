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

#include "../include/main.h"

namespace sensors {
	Quad::Quad(unsigned char port1,
						 unsigned char port2,
						 bool					 inverted):inverted(inverted) {
		ports[0] = port1;
		ports[1] = port2;
		zero		 = 0;
		request  = 0;
	}

	void Quad::init(void) {
		enc = encoderInit(Quad::ports[0], Quad::ports[1], Quad::inverted);
	} // Quad::init

	long Quad::value(void) {
		return encoderGet(enc) - zero;
	} // Quad::value

	void Quad::reset(void) {
		zero		= encoderGet(enc);
		request = 0;
	} // Quad::reset

	Gyroscope::Gyroscope(unsigned char port,
											 unsigned int  calibration):port(port),
																									calibration(calibration) {
		zero		= 0;
		request = 0;
	}

	void Gyroscope::init(void) {
		Gyroscope::gyro = gyroInit(port, calibration);
	} // Gyroscope::init

	long Gyroscope::value(void) {
		return gyroGet(Gyroscope::gyro) - zero;
	} // Gyroscope::value

	void Gyroscope::reset(void) {
		zero		= gyroGet(Gyroscope::gyro);
		request = 0;
	} // Gyroscope::reset

	Pot::Pot(unsigned char port,
					 bool					 inverted):port(port), inverted(inverted) {
		zero		= 0;
		request = 0;
	}

	void Pot::init(void) {
		analogCalibrate(port);
	} // Pot::init

	long Pot::value(void) {
		return (analogReadCalibrated(port) - zero) * ((inverted) ? -1 : 1);
	} // Pot::value

	void Pot::reset(void) {
		zero		= analogReadCalibrated(port);
		request = 0;
	} // Pot::reset

	Sonic::Sonic(unsigned char port1,
							 unsigned char port2) {
		ports[0] = port1;
		ports[1] = port2;
	}

	void Sonic::init(void) {
		sonic = ultrasonicInit(Sonic::ports[0], Sonic::ports[1]);
	} // Sonic::init

	long Sonic::value(void) {
		return ultrasonicGet(sonic);
	} // Sonic::value

	Button::Button(unsigned char port,
								 bool					 inverted):port(port), inverted(inverted) {}

	void Button::init(void) {
		pinMode(port, INPUT);
	} // Button::init

	bool Button::value(void) {
		return (digitalRead(port)) ? ((inverted) ? false : true)
					 : ((inverted) ? true : false);
	} // Button::value

	void reset(void) {
		left.reset();
		right.reset();
	} // reset
}		// namespace sensors
