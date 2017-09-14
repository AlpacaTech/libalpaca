/*
 * @file motors.cpp
 * @brief Source file of hardware abstraction for motors and slewing
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

#include "../include/alpaca/motors.hpp"

namespace Alpaca {
	void Motor::set(int p) {
		power          = (int)(scale(p * inverted));
		slew->lastTime = millis();
		slew->request  = power;
	} /* Motor::set */

	Motor::Motor(char  inverted,
	             char  motorPort,
	             bool  isSlew,
	             float slewRate,
	             float(*scale)(int)) : inverted(inverted), scale(scale) {
		static unsigned char p = motorPort;

		port                       = (motorPort != -1) ? motorPort : p++;
		slew::list[port - 1] = MotorData();
		this->slew                       = &slew::list[port - 1];
		this->slew->rate                 = slewRate;
		this->slew->on                   = isSlew;
	}

	namespace slew {
		Motor::MotorData  list[10];
		TaskHandle handle;

		void slew(void *none) {
			unsigned long int current;

			while (true) {
				current = millis();

				for (size_t i = 0; i < 10; i++) {
					Motor::MotorData *m = &list[i];

					if ((m->request == m->lastPower) || !m->on) {
						motorSet(i + 1, m->request);
						continue;
					}

					int change =
						(m->request >
						 m->lastPower) ? ((millis() -
															 m->lastTime) *
															m->rate) : ((millis() - m->lastTime) * -m->rate);

					list[i].lastPower += change;
						motorSet(i + 1, list[i].lastPower);
					list[i].lastTime = current;
				}
				delay(slewWait);
			}
			(void)none;
		} /* slew */

		void init(void) {
			Motor::MotorData default_motor;

			default_motor.lastTime  = millis();
			default_motor.lastPower = 0;
			default_motor.request   = 0;

			for (size_t i = 1; i <= 11; i++) {
				list[i] = default_motor;
			}
			handle = taskCreate(&slew, TASK_DEFAULT_STACK_SIZE, NULL,
													TASK_PRIORITY_DEFAULT + 1);
		} /* init */
	}   /* namespace slew */
}     /* namespace Alpaca */
