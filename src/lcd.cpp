/*
 * @file lcd.cpp
 * @brief Source for utilities interacting with the LCD
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

#include "../include/lcd.hpp"

LcdScreen::LcdScreen(std::string line1,
                     std::string line2) : line1(line1), line2(line2) {}

std::string LcdScreen::content(int line) {
	switch (line) {
	case 1:
		return line1;

	case 2:
		return line2;

	default:
		return std::string("0");
	} /* switch */
} /* content */

std::string LcdScreen::content(int line, std::string newContent) {
	switch (line) {
	case 1:
		return line1 = newContent;

	case 2:
		return line2 = newContent;

	default:
		return std::string("0");
	} /* switch */
} /* content */

Lcd::Lcd(PROS_FILE *port,
         bool       backlight) : port(port), backlight(backlight) {}

void Lcd::init() {
	lcdInit(port);
	lcdSetBacklight(port, backlight);
} /* init */

void Lcd::set(LcdScreen *screen) {
	lcdSetText(port, 1, screen->content(1).c_str());
	lcdSetText(port, 2, screen->content(2).c_str());
} /* set */
