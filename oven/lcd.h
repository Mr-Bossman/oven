#include "common.h"


#ifndef LCD_H_
#define LCD_H_
// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00
uint8_t _numlines;
uint8_t _row_offsets[4];

	extern void lcd_init(uint8_t cols, uint8_t rows);

	extern void lcd_clear();
	extern void lcd_home();

	extern void lcd_noDisplay();
	extern void lcd_display();
	extern void lcd_noBlink();
	extern void lcd_blink();
	extern void lcd_noCursor();
	extern void lcd_cursor();
	extern void lcd_scrollDisplayLeft();
	extern void lcd_scrollDisplayRight();
	extern void lcd_leftToRight();
	extern void lcd_rightToLeft();
	extern void lcd_autoscroll();
	extern void lcd_noAutoscroll();

	extern void lcd_setRowOffsets(int row1, int row2, int row3, int row4);
	extern void lcd_createChar(uint8_t, uint8_t[]);
	extern void lcd_setCursor(uint8_t, uint8_t);
	extern size_t lcd_write(uint8_t);
	extern void lcd_command(uint8_t);
	
	char* console[15];
	extern uint8_t lcd_print(char str[]);
	extern void lcd_updateScreen(uint8_t line);
	extern inline void lcd_printline(char str[]);



#endif /* INCFILE1_H_ */