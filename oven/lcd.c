#include "lcd.h"

static uint8_t _displaycontrol;
static uint8_t _displaymode;
static uint8_t _displayfunction;
static uint8_t _numlines;
static void lcdwrite8bits(uint8_t);
static void pulseEnable();

extern void lcdbegin(uint8_t cols, uint8_t lines) {
	_displayfunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;
	if (lines > 1) _displayfunction |= LCD_2LINE;
	_numlines = lines;
	DDRB |= 3;
	DDRD = UINT8_MAX;
	_delay_ms(50);
	PORTB &= ~(3);
	lcdcommand(LCD_FUNCTIONSET | _displayfunction);
	_delay_ms(5);
	lcdcommand(LCD_FUNCTIONSET | _displayfunction);
	_delay_ms(1);
	lcdcommand(LCD_FUNCTIONSET | _displayfunction);
	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	lcddisplay();
	lcdclear();
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
	lcdcommand(LCD_ENTRYMODESET | _displaymode);

}

extern void lcdclear()
{
	lcdcommand(LCD_CLEARDISPLAY);
	_delay_ms(2);
}

extern void lcdhome()
{
	lcdcommand(LCD_RETURNHOME);
	_delay_ms(2);
}

extern void lcdsetCursor(uint8_t col, uint8_t row)
{
	register uint8_t offset = 0;
	switch (row) {
		case 0: offset = 0;
		break;
		case 1:offset = 0x40;
		break;
		case 2:offset = col;
		break;
		case 3:offset = 0x40 + col;
		break;
		default:offset = 0;
		break;
	}
lcdcommand(LCD_SETDDRAMADDR | (col + offset));
}

extern void lcdnoDisplay() {
	_displaycontrol &= ~LCD_DISPLAYON;
	lcdcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}
extern void lcddisplay() {
	_displaycontrol |= LCD_DISPLAYON;
	lcdcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

extern void lcdnoCursor() {
	_displaycontrol &= ~LCD_CURSORON;
	lcdcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}
extern void lcdcursor() {
	_displaycontrol |= LCD_CURSORON;
	lcdcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

extern void lcdnoBlink() {
	_displaycontrol &= ~LCD_BLINKON;
	lcdcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}
extern void lcdblink() {
	_displaycontrol |= LCD_BLINKON;
	lcdcommand(LCD_DISPLAYCONTROL | _displaycontrol);
}

extern void lcdscrollDisplayLeft(void) {
	lcdcommand(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
extern void lcdscrollDisplayRight(void) {
	lcdcommand(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

extern void lcdleftToRight(void) {
	_displaymode |= LCD_ENTRYLEFT;
	lcdcommand(LCD_ENTRYMODESET | _displaymode);
}

extern void lcdrightToLeft(void) {
	_displaymode &= ~LCD_ENTRYLEFT;
	lcdcommand(LCD_ENTRYMODESET | _displaymode);
}

extern void lcdautoscroll(void) {
	_displaymode |= LCD_ENTRYSHIFTINCREMENT;
	lcdcommand(LCD_ENTRYMODESET | _displaymode);
}

extern void lcdnoAutoscroll(void) {
	_displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
	lcdcommand(LCD_ENTRYMODESET | _displaymode);
}

extern void lcdsend(uint8_t value, bool mode) {
	if(mode)
	PORTB |= 1;
	else
	PORTB &= ~(1);
	lcdwrite8bits(value);
}


extern inline void lcdwrite(uint8_t value) {
	lcdsend(value, true);
}
extern inline void lcdcommand(uint8_t value) { 
	lcdsend(value, false); 
}
static void pulseEnable() {
	PORTB &= ~(1<<1);
	_delay_ms(10);
	PORTB |= 1<<1;
	_delay_ms(10);
	PORTB &= ~(1<<1);
	_delay_ms(10);
}

static void lcdwrite8bits(uint8_t value) {
	PORTD = value;
	pulseEnable();
}