#include "common.h"
#include "lcd.h"
void push(char *ptr){
	memmove(console+1,console,13);
	console[0] = ptr;
}
void pop(){
	memcpy(console,console+1,13);
}
void cls(){
	memset(console,0,15);
}
extern uint8_t lcd_print(char str[]){
	push(str);
	for(uint16_t i = 0; str[i]; i++) {
		if (str[i] == '\n')
			push(str + i + 1);
		if(str[i] == '\r')
			pop();
 	}
	 return 0;
}
void lcd_updateScreen(uint8_t line){
	
	for(int8_t l = 1; l >= 0  ;l--){
		char * curline = console[l+line];
		uint8_t i = 0;
		if(curline){
			for(; i < 0x28 && curline[i] && curline[i] != '\n'; i++) {
				//if(i > _row_offsets[2])lcd_autoscroll();
				lcd_write(curline[i]);
			}
		}
		for(; i < 0x28; i++) 
			lcd_write(' ');
	}

}
extern inline void lcd_printline(char str[]){
	lcd_print(str);
	lcd_updateScreen(0);
}