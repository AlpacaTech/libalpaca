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
                     std::string line2) {
	_content[0] = line1;
	_content[1] = line2;
}

std::string LcdScreen::content(int line) {
	return _content[line];
} /* content */

std::string LcdScreen::content(int line, std::string newContent) {
	return _content[line] = newContent;
} /* content */

Lcd::Lcd(PROS_FILE *port,
         bool       backlight) : port(port), backlight(backlight) {}

void Lcd::init() {
	lcdInit(port);
	lcdSetBacklight(port, backlight);
} /* init */

void Lcd::set(LcdScreen *screen) {
	for (int line = 0; line < 2; line++) {
		lcdSetText(port, line, screen->content(line).c_str());
	}
} /* set */
