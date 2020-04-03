#ifndef LCD_H
#define LCD_H
#include "commonH.h"

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



extern void lcdbegin(uint8_t cols, uint8_t rows);

extern void lcdclear();
extern void lcdhome();

extern void lcdnoDisplay();
extern void lcddisplay();
extern void lcdnoBlink();
extern void lcdblink();
extern void lcdnoCursor();
extern void lcdcursor();
extern void lcdscrollDisplayLeft();
extern void lcdscrollDisplayRight();
extern void lcdleftToRight();
extern void lcdrightToLeft();
extern void lcdautoscroll();
extern void lcdnoAutoscroll();

extern void lcdsetRowOffsets(int row1, int row2, int row3, int row4);
extern void lcdcreateChar(uint8_t, uint8_t[]);
extern void lcdsetCursor(uint8_t, uint8_t);
extern void lcdsend(uint8_t, bool);

extern void lcdcommand(uint8_t value);
extern void lcdwrite(uint8_t value);

#endif
