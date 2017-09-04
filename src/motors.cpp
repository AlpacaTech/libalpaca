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
	void Motor::set(int _power) {
		power          = _power * inverted * scale;
		slew->lastTime = millis();
		slew->request  = power;
	} /* Motor::set */

	namespace motors {
		Motor init(char  port,
		           int   inverted,
		           bool  slew,
		           float slewRate,
		           float scale) {
			static unsigned char p = 0;
			Motor motor;

			motor.port                 = (port != -1) ? port : p++;
			motor.inverted             = inverted;
			motor.scale                = scale;
			slew::list[motor.port - 1] = MotorData();
			motor.slew                 = &slew::list[motor.port - 1];
			motor.slew->rate           = slewRate;
			motor.slew->on             = slew;
			return motor;
		} /* init */

		namespace slew {
			MotorData  list[10];
			TaskHandle handle;

			void slew(void *none) {
				unsigned long int current;

				while (true) {
					current = millis();

					for (size_t i = 0; i < 10; i++) {
						MotorData *m = &list[i];

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
				free(none);
			} /* slew */

			void init(void) {
				MotorData default_motor;

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
	}     /* namespace motors */
}       /* namespace Alpaca */
