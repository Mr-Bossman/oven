
#include "common.h"
#include "lcd.h"
#include "analog.h"
#include "timer.h"
#include "menus.h"
#include "UI.h"
#include "temp_control.h"
#include "MAX31855.h"
#include "exit.h"

#include <util/delay.h>
void screen(bool rise,uint16_t temp,uint16_t l,uint16_t T){
		static char dis[20];
		sprintf(dis,"%s %u\n %u, %u",(rise)?"s":"r",T,temp,l);
		lcd_print(dis);
		lcd_updateScreen(0);
		_delay_ms(10);
}

int main(void) {
	lcd_init(16,2);
	InitADC();
	initTime();
		DDRC |= 2; // realy pin

	//DDRB |= (5 << 3); // init temp spi
	//PORTB |= (1 << 5);
	PORTB |= 1<<2; //init button
	PORTB |= 3<<3; //init button

	uint32_t a[6] = {0};
	Options(a);
	//while(1){
		update(a,&screen);

	//}
	exit_code(0);
}