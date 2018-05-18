#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "LCD/lcd.h"
#define true 1
#define false 0

LCD lcd;

int main(void)
{
	lcd.begin();
	lcd.writeString("IT'S WORKING!",1);
	lcd.setCursor(0,10);
	lcd.writeString("Nice!",2);
	lcd.render();
	_delay_ms(1000);
	lcd.clear();
	lcd.render();

    while(1) {
		_delay_ms(10);
    }
}
