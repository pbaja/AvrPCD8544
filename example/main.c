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

#include "nlcd.h"

#define F_CPU 16000000UL

int main(void)
{
	struct lcd_nokia lcd;

	lcd_nokia_init();
	lcd_nokia_clear(&lcd);
	lcd_nokia_write_string(&lcd, "IT'S WORKING!",1);
	lcd_nokia_set_cursor(&lcd, 0, 10);
	lcd_nokia_write_string(&lcd, "Nice!", 3);
	lcd_nokia_render(&lcd);

	for (;;) {
		_delay_ms(1000);
	}
}
