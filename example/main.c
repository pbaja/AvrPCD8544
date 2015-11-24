/* Nokia 5110 LCD AVR Library example
 *
 * Copyright (C) 2015 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 *
 * Original library written by SkewPL, http://skew.tk
 */

#include <avr/io.h>
#include <util/delay.h>

#include "nokia5110.h"

#define F_CPU 16000000UL

int main(void)
{
	Nokia5110 lcd;

	nokia_lcd_init();
	nokia_lcd_clear(&lcd);
	nokia_lcd_write_string(&lcd, "IT'S WORKING!",1);
	nokia_lcd_set_cursor(&lcd, 0, 10);
	nokia_lcd_write_string(&lcd, "Nice!", 3);
	nokia_lcd_render(&lcd);

	for (;;) {
		_delay_ms(1000);
	}
}
