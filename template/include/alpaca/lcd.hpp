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

#include "../API.hpp"
#include "util.hpp"

/*
 * An LcdFrame is a node in a linked list of LcdFrames, and has a child node
 * as well
 */
class LcdFrame {
	public:

		LcdFrame(const char *line1,
		         const char *line2,
		         LcdFrame   *parent = NULL,
		         LcdFrame   *prev   = NULL,
		         LcdFrame   *next   = NULL,
		         LcdFrame   *child  = NULL);

		/*
		 * Get the content on the specified line
		 */
		const char* content(int line);
		const char* content(int         line,
		                    const char *newContent);

		/*
		 * The parent LcdFrame
		 */
		LcdFrame *parent;

		/*
		 * The previous screen in the linked list
		 */
		LcdFrame *prev;

		/*
		 * The next screen in the linked list
		 */
		LcdFrame *next;

		/*
		 * The child of this node
		 */
		LcdFrame *child;

	private:

		/*
		 * The content of this screen
		 */
		const char *_content[2];
}; /* class LcdFrame */

/*
 * Lcd screens can be very useful for displaying basic information, and possibly
 * selecting something based on that information.
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
		void set(LcdFrame *screen);

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

		/*
		 * The current screen the Lcd is displaying
		 */
		LcdFrame *current;
}; /* class Lcd */

#endif /* end of include guard: LCD_HPP */
