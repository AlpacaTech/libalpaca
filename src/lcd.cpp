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

LcdFrame::LcdFrame(const char *line1,
                   const char *line2,
                   LcdFrame   *parent,
                   LcdFrame   *prev,
                   LcdFrame   *next,
                   LcdFrame   *child) : parent(parent), prev(prev), next(next),
	                                      child(child) {
	_content[0] = line1;
	_content[1] = line2;
}

const char * LcdFrame::content(int line) {
	return _content[line - 1];
} /* content */

const char * LcdFrame::content(int line, const char *newContent) {
	return _content[line - 1] = newContent;
} /* content */

Lcd::Lcd(PROS_FILE *port,
         bool       backlight) : port(port), backlight(backlight) {}

void Lcd::init() {
	lcdInit(port);
	lcdSetBacklight(port, backlight);
} /* init */

void Lcd::set(LcdFrame *screen) {
	current = screen;
	lcdSetText(port, 1, screen->content(1));
	lcdSetText(port, 2, screen->content(2));
} /* set */
