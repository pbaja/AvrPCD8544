#ifndef LCD_H_
#define LCD_H_

class LCD {
	private:
		static const uint8_t LCD_SCE      = PD4; //Also known as CE
		static const uint8_t LCD_RST      = PD3;
		static const uint8_t LCD_DC       = PD5;
		static const uint8_t LCD_DIN      = PD6; //Also known as DATA
		static const uint8_t LCD_CLK      = PD7;
		static const uint8_t LCD_CONTRAST = 0x40;

		uint8_t SCREEN[504];
		uint8_t CURSOR_X;
		uint8_t CURSOR_Y;

		void writeCmd(uint8_t cmd);
		void writeData(uint8_t data);
		void write(uint8_t bytes, uint8_t isdata);
	public:
		//Must be called once before any other function, initializes display
		void begin(void);
		//Render screen to display
		void render(void);
		//Clear screen
		void clear(void);
		//Power on/off display (0=OFF, 1=ON)
		void setPower(uint8_t on);
		//Set single pixel
		void setPixel(uint8_t x, uint8_t y, uint8_t value);
		//Set cursor position
		void setCursor(uint8_t x, uint8_t y);
		//Draw single char with 1-6 scale
		void writeChar(char code,uint8_t scale);
		//Draw string. Example: writeString("abc",3);
		void writeString(char s[],uint8_t scale);
	};

#endif /* LCD_H_ */
