#include "lcd.h"

#include <util/delay.h>
static void lcd_send(uint8_t, uint8_t);
static void lcd_write4bits(uint8_t);
static void lcd_write8bits(uint8_t);
static void lcd_pulseEnable();

static uint8_t _displaycontrol;
static uint8_t _displaymode;
static uint8_t _displayfunction;


// When the display powers up, it is configured as follows:
//
// 1. Display clear
// 2. Function set:
//    DL = 1; 8-bit interface data
//    N = 0; 1-line display
//    F = 0; 5x8 dot character font
// 3. Display on/off control:
//    D = 0; Display off
//    C = 0; Cursor off
//    B = 0; Blinking off
// 4. Entry mode set:
//    I/D = 1; Increment by 1
//    S = 0; No shift
//
// Note, however, that resetting the Arduino doesn't reset the LCD, so we
// can't assume that its in that state when a sketch starts (and the
// LiquidCrystal constructor is called).

extern void lcd_init(uint8_t cols, uint8_t lines) {
	memset(console,0,14);
	uint8_t dotsize = LCD_5x8DOTS;
	DDRD = 0xFF;
	DDRB |= 3;

	if (0)
	_displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
	else
	_displayfunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;

	if (lines > 1) {
		_displayfunction |= LCD_2LINE;
	}
	_numlines = lines;

	lcd_setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);

	// for some 1 line displays you can select a 10 pixel high font
	if ((dotsize != LCD_5x8DOTS) && (lines == 1)) {
		_displayfunction |= LCD_5x10DOTS;
	}

		DDRD = 0xFF;
		DDRB |= 3;
		PORTD = 0;
		PORTB &= ~(3);

	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way before 4.5V so we'll wait 50
	_delay_us(50000);
	// Now we pull both RS and R/W low to begin commands

	
	//put the LCD into 4 bit or 8 bit mode
	if (! (_displayfunction & LCD_8BITMODE)) {
		// this is according to the hitachi HD44780 datasheet
		// figure 24, pg 46

		// we start in 8bit mode, try to set 4 bit mode
		lcd_write4bits(0x03);
		_delay_us(4500); // wait min 4.1ms
		// second try
		lcd_write4bits(0x03);
		_delay_us(4500); // wait min 4.1ms
		
		// third go!
		lcd_write4bits(0x03);
		_delay_us(150);

		// finally, set to 4-bit interface
		lcd_write4bits(0x02);
		} else {
		// this is according to the hitachi HD44780 datasheet
		// page 45 figure 23

		// Send function set command sequence
		lcd_command(LCD_FUNCTIONSET | _displayfunction);
		_delay_us(4500);  // wait more than 4.1ms

		// second try
		lcd_command(LCD_FUNCTIONSET | _displayfunction);
		_delay_us(150);

		// third go
		lcd_command(LCD_FUNCTIONSET | _displayfunction);
	}

	// finally, set # lines, font size, etc.
	lcd_command(LCD_FUNCTIONSET | _displayfunction);

	// turn the display on with no cursor or blinking default
	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	lcd_display();

	// clear it off
	lcd_clear();

	// Initialize to default text direction (for romance languages)
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	// set the entry mode
	lcd_command(LCD_ENTRYMODESET | _displaymode);

}

extern void lcd_setRowOffsets(int row0, int row1, int row2, int row3)
{
	_row_offsets[0] = row0;
	_row_offsets[1] = row1;
	_row_offsets[2] = row2;
	_row_offsets[3] = row3;
}

/********** high level commands, for the user! */
extern void lcd_clear()
{
	lcd_command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
	_delay_us(2000);  // this command takes a long time!
}

extern void lcd_home()
{
	lcd_command(LCD_RETURNHOME);  // set cursor position to zero
	_delay_us(2000);  // this command takes a long time!
}

extern void lcd_setCursor(uint8_t col, uint8_t row)
{
	const size_t max_lines = sizeof(_row_offsets) / sizeof(*_row_offsets);
	if ( row >= max_lines ) {
		row = max_lines - 1;    // we count rows starting w/0
	}
	if ( row >= _numlines ) {
		row = _numlines - 1;    // we count rows starting w/0
	}
	
	lcd_command(LCD_SETDDRAMADDR | (col + _row_offsets[row]));
}

// Turn the display on/off (quickly)
extern void lcd_noDisplay() {
	_displaycontrol &= ~LCD_DISPLAYON;
	lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}
extern void lcd_display() {
	_displaycontrol |= LCD_DISPLAYON;
	lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
extern void lcd_noCursor() {
	_displaycontrol &= ~LCD_CURSORON;
	lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}
extern void lcd_cursor() {
	_displaycontrol |= LCD_CURSORON;
	lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
extern void lcd_noBlink() {
	_displaycontrol &= ~LCD_BLINKON;
	lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}
extern void lcd_blink() {
	_displaycontrol |= LCD_BLINKON;
	lcd_command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
extern void lcd_scrollDisplayLeft(void) {
	lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
extern void lcd_scrollDisplayRight(void) {
	lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
extern void lcd_leftToRight(void) {
	_displaymode |= LCD_ENTRYLEFT;
	lcd_command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
extern void lcd_rightToLeft(void) {
	_displaymode &= ~LCD_ENTRYLEFT;
	lcd_command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
extern void lcd_autoscroll(void) {
	_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	lcd_command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
extern void lcd_noAutoscroll(void) {
	_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	lcd_command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
extern void lcd_createChar(uint8_t location, uint8_t charmap[]) {
	location &= 0x7; // we only have 8 locations 0-7
	lcd_command(LCD_SETCGRAMADDR | (location << 3));
	for (int i=0; i<8; i++) {
		lcd_write(charmap[i]);
	}
}

/*********** mid level commands, for sending data/cmds */

extern void lcd_command(uint8_t value) {
	lcd_send(value, 0);
}

extern size_t lcd_write(uint8_t value) {
	lcd_send(value, 1);
	return 1; // assume sucess
}

/************ low level data pushing commands **********/

// write either command or data, with automatic 4/8-bit selection
static void lcd_send(uint8_t value, uint8_t mode) {
	PORTB = (mode)? PORTB | 1: PORTB & ~(1);	
	if (_displayfunction & LCD_8BITMODE) {
		lcd_write8bits(value);
		} else {
		lcd_write4bits(value>>4);
		lcd_write4bits(value);
	}
}

static  void lcd_pulseEnable(void) {
	PORTB |= 2;
	_delay_us(1);
	PORTB &= ~(2);
	_delay_us(1);    // enable pulse must be >450ns
	PORTB |= 2;
	_delay_us(40);   // commands need > 37us to settle
}

static void lcd_write4bits(uint8_t value) {
	PORTD = value;
	lcd_pulseEnable();
}

static void lcd_write8bits(uint8_t value) {
	PORTD = value;
	lcd_pulseEnable();
}
