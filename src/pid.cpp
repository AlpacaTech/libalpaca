/*
 * @file pid.cpp
 * @brief Enables fewer steps in the implementation of PID control
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

void Pid::loop() {
	float current;
	float error;
	float lastError = 0;
	float integral  = 0;
	float derivative;
	float power;

	bool done = false;

	std::vector<bool> success;

	settings->system.sensor->reset();

	do {
		delay(25);
		current = settings->system.sensor->value();
		error   = settings->system.sensor->request() - current;

		if ((unsigned int)abs((int)error) <= settings->precision) {
			success.push_back(true);

			if (success.size() > 4) {
				return;
			}
			continue;
		}
		success.clear();
		integral = (settings->Ki != 0 && abs((int)error) < settings->iLimit)
		           ? (integral + error)
							 : 0;
		derivative = error - lastError;
		lastError  = error;
		power      =
		  (settings->Kp *
		   error) + (settings->Ki * integral) + (settings->Kd * derivative);
		power = clipNum(power /* 8.1f / powerLevelMain() */,
		                settings->max,
		                settings->min);

		for (auto m : *settings->system.motors) {
			m.set(power);
		}
	} while (!done);
} /* loop */

Pid::Settings::Settings(float        Kp,
                        float        Ki,
                        float        Kd,
                        System       system,
                        int          max,
                        int          min,
                        int          iLimit,
                        unsigned int precision):max(max), min(min),
	                                              iLimit(iLimit), Kp(Kp),
	                                              Ki(Ki), Kd(Kd),
	                                              precision(precision),
	                                              system(system) {}

Pid::Pid(float        Kp,
         float        Ki,
         float        Kd,
         long         target,
         System       system,
         int          max,
         int          min,
         int          iLimit,
         unsigned int precision):target(target) {
	settings = new Settings { Kp, Ki, Kd, system, max, min, iLimit, precision };
	loop();
	delete settings;
}

Pid::Pid(Settings *settings,
         long      target):settings(settings), target(target) {
	loop();
}
