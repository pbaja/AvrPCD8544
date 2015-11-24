/* Nokia 5110 LCD AVR Library
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

#ifndef __nokia_lcd_H__
#define __nokia_lcd_H__

#include <avr/pgmspace.h>
#include <stdint.h>

/*
 * LCD's port
 */
#define PORT_LCD PORTB
#define DDR_LCD DDRB

/*
 * LCD's pins
 */
#define LCD_SCE PB1
#define LCD_RST PB2
#define LCD_DC PB3
#define LCD_DIN PB4
#define LCD_CLK PB5

#define LCD_CONTRAST 0x40

typedef struct nokia5110_t Nokia5110;

struct nokia5110_t {
	uint8_t screen[504];
	uint8_t cursor_x;
	uint8_t cursor_y;
};

/*
 * Must be called once before any other function, initializes display
 */
void nokia_lcd_init(void);

/*
 * Clear screen
 */
void nokia_lcd_clear(Nokia5110 *lcd);

/**
 * Power of display
 * @lcd: lcd nokia struct
 * @on: 1 - on; 0 - off;
 */
void nokia_lcd_power(Nokia5110 *lcd, uint8_t on);

/*
 * Set single pixel
 */
void nokia_lcd_set_pixel(Nokia5110 *lcd, uint8_t x, uint8_t y, uint8_t value);

/*
 * Draw single char with 1-6 scale
 */
void nokia_lcd_write_char(Nokia5110 *lcd, char code, uint8_t scale);

/*
 * Draw string. Example: writeString("abc",3);
 */
void nokia_lcd_write_string(Nokia5110 *lcd, const char *str, uint8_t scale);

/*
 * Set cursor position
 */
void nokia_lcd_set_cursor(Nokia5110 *lcd, uint8_t x, uint8_t y);

/*
 * Render screen to display
 */
void nokia_lcd_render(Nokia5110 *lcd);


#endif
