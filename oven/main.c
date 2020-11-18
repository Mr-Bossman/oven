
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
void screen(struct tempC data){
		static char dis[20];
		if(data.stableTemp)
			sprintf(dis,"%s %u\n %u, %u",(data.stableTemp)?"s":"r",(uint16_t)(data.times-(Time()/1000)),(get_temp() >> 2),data.temp);
		else if (data.temp)
			sprintf(dis,"%s %u\n %u, %u",(data.stableTemp)?"s":"r",data.rise,(get_temp() >> 2),data.temp);
		else 
			sprintf(dis,"%s %u\n %u, %u",(data.stableTemp)?"s":"r",(uint16_t)(data.times-(Time()/1000)),(get_temp() >> 2),data.rise);

		lcd_print(dis);
		lcd_updateScreen(0);
		_delay_ms(10);
}

int main(void) {
	lcd_init(16,2);
	InitADC();
	initTime();
	DDRC |= 4; // realy pin
	DDRC |= (1<<5); // thermo cpule
	DDRE |= (1<<2);

	PORTB |= 1<<2; //init button
	PORTB |= 3<<3; //init button

	while(1){
			struct tempC a[6] = {0};

		Options(a);
		update(a,&screen);
	}
	exit_code(0);
}