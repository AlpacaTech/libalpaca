/*
 * @file lcd.hpp
 * @brief Utilities for interacting with the LCD
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

#ifndef LCD_HPP
#define LCD_HPP

#include <map>
#include <string>
#include "API.h"
#include "util.h"

/*
 * An LcdScreen is a node in a tree of LcdScreens, and can be set to the Lcd
 */
class LcdScreen {
	public:

		/*
		 * The children of this node
		 */
		std::map<std::string, LcdScreen> c;

		/*
		 * Get the content on the specified line
		 */
		std::string content(int line);
		std::string content(int         line,
		                    std::string newContent);

		LcdScreen(std::string line1,
		          std::string line2);

	private:

		/*
		 * The two lines of Lcd content
		 */
		std::string _content[2];
}; /* class LcdScreen */

/*
 * Lcd screens can be very useful for displaying basic information, and possibly
 ******selecting something based on that information.
 */
class Lcd {
	public:

		/*
		 * Initialize the Lcd - call in initialize()
		 */
		void init();

		/*
		 * Set the Lcd to display a given screen
		 */
		void set(LcdScreen *screen);

		Lcd(PROS_FILE *port = uart1,
		    bool       backlight = true);

	private:

		/*
		 * The port the Lcd is plugged into
		 */
		PROS_FILE *port;

		/*
		 * Whether or not the Lcd should have a backlight
		 */
		bool backlight;
}; /* class Lcd */

#endif /* end of include guard: LCD_HPP */
