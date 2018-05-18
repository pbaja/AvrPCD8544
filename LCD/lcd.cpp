#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>
#include "charset.cpp"
#include "lcd.h"

void LCD::begin(void) {
	//Set pins as output
	DDRD |= (1<<LCD_SCE);
	DDRD |= (1<<LCD_RST);
	DDRD |= (1<<LCD_DC);
	DDRD |= (1<<LCD_DIN);
	DDRD |= (1<<LCD_CLK);

	//Reset display
	PORTD |= (1<<LCD_RST);
	PORTD |= (1<<LCD_SCE);
	_delay_ms(10);
	PORTD &= ~(1<<LCD_RST);
	_delay_ms(70);
	PORTD |= (1<<LCD_RST);
	
	//Initialize display
	PORTD &= ~(1<<LCD_SCE);   // Enable controller
	writeCmd(0x21);  // -LCD Extended Commands mode-
	writeCmd(0x13);  // LCD bias mode 1:48
	writeCmd(0x06);  // Set temperature coefficient
	writeCmd(0xC2);  // Default VOP (3.06 + 66 * 0.06 = 7V)
	writeCmd(0x20);  // Standard Commands mode, powered down
	writeCmd(0x09);  // LCD in normal mode

	//Clear LCD RAM
	writeCmd(0x80);
	writeCmd(0x40);
	for(int i=0;i<504;i++) {writeData(0x00);}

	//Activate LCD
	writeCmd(0x08);
	writeCmd(0x0C);
}

void LCD::clear(void) {
	//Set column and row to 0
	writeCmd(0x80);
	writeCmd(0x40);
	//Cursor too
	CURSOR_X = 0;
	CURSOR_Y = 0;
	//Clear everything (504 bytes = 84cols * 48 rows / 8 bits)
	for(int i=0;i<504;i++) {SCREEN[i] = 0x00;}
}

void LCD::setPower(uint8_t on) {
	writeCmd(on ? 0x20 : 0x24);
}

void LCD::setPixel(uint8_t x, uint8_t y, uint8_t value) {
	uint8_t &byte = SCREEN[y/8*84+x];
	if (value) byte |= (1<<(y%8));
	else byte &= ~(1<<(y%8));
}
void LCD::writeChar(char code,uint8_t scale) {
	uint8_t x,y;
	for(x=0;x<5*scale;x++) {
		for(y=0;y<7*scale;y++) {
			if(pgm_read_byte(&CHARSET[code-32][x/scale]) & (1<<y/scale)) setPixel(CURSOR_X+x,CURSOR_Y+y,1);
			else setPixel(CURSOR_X+x,CURSOR_Y+y,0);
		}
	}
	CURSOR_X += 5*scale+1;
	if(CURSOR_X >= 84) {CURSOR_X = 0;CURSOR_Y+=7*scale+1;}
	if(CURSOR_Y >= 48) {CURSOR_X = 0;CURSOR_Y=0;}
}
void LCD::writeString(char s[], uint8_t scale) {
	int i=0;
	while(s[i]) {
		writeChar(s[i],scale);
		i++;
	}
	/*for(uint8_t i=0;i<len;i++) {
		writeChar(s[i],scale);
	}*/
}

void LCD::setCursor(uint8_t x, uint8_t y) {
	CURSOR_X = x;
	CURSOR_Y = y;
}

/*
 * LOW LEVEL FUNCTIONS
 */

void LCD::render(void) {
	//Set column and row to 0
	writeCmd(0x80);
	writeCmd(0x40);

	//Write screen to display
	for(int i=0;i<504;i++) {writeData(SCREEN[i]);}
}

void LCD::write(uint8_t bytes, uint8_t isdata) {
	//Enable controller
	PORTD &= ~(1<<LCD_SCE);

	//We are sending data
	if(isdata) PORTD |= (1<<LCD_DC); 
	//We are sending commands
	else PORTD &= ~(1<<LCD_DC);

	//Send bytes
	for(unsigned char i=0;i<8;i++) {
		//Set data pin to byte state
		if((bytes>>(7-i)) & 0x01) PORTD |= (1<<LCD_DIN);
		else PORTD &= ~(1<<LCD_DIN);
		
		//Blink clock
		PORTD |= (1<<LCD_CLK);
		PORTD &= ~(1<<LCD_CLK);
	}

	//Disable controller
	PORTD |= (1<<LCD_SCE);
}
void LCD::writeCmd(uint8_t cmd) {write(cmd,0);}
void LCD::writeData(uint8_t data) {write(data,1);}
