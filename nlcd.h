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

#ifndef __LCD_NOKIA_H__
#define __LCD_NOKIA_H__

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

typedef struct lcd_nokia LcdNokia;

struct lcd_nokia {
	uint8_t screen[504];
	uint8_t cursor_x;
	uint8_t cursor_y;
};

/*
 * Must be called once before any other function, initializes display
 */
void lcd_nokia_init(void);

/*
 * Clear screen
 */
void lcd_nokia_clear(LcdNokia *lcd);

/**
 * Power of display
 * @lcd: lcd nokia struct
 * @on: 1 - on; 0 - off;
 */
void lcd_nokia_power(LcdNokia *lcd, uint8_t on);

/*
 * Set single pixel
 */
void lcd_nokia_set_pixel(LcdNokia *lcd, uint8_t x, uint8_t y, uint8_t value);

/*
 * Draw single char with 1-6 scale
 */
void lcd_nokia_write_char(LcdNokia *lcd, char code, uint8_t scale);

/*
 * Draw string. Example: writeString("abc",3);
 */
void lcd_nokia_write_string(LcdNokia *lcd, const char *str, uint8_t scale);

/*
 * Set cursor position
 */
void lcd_nokia_set_cursor(LcdNokia *lcd, uint8_t x, uint8_t y);

/*
 * Render screen to display
 */
void lcd_nokia_render(LcdNokia *lcd);


#endif
