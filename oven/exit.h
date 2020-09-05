/*
 * exit.h
 *
 * Created: 8/31/2020 5:07:05 PM
 *  Author: jesse
 */ 


#ifndef EXIT_H_
#define EXIT_H_

#include "common.h"
#include "lcd.h"

void exit_code(int8_t code){
	char dis[20];
	sprintf(dis,"%s \nExit code: %d",(code)?"Program failed...":"Success!!!",code);
	lcd_print(dis);
	lcd_updateScreen(0);
	DDRB = 0;
	DDRC = 0;
	DDRD = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	exit(0);
}




#endif /* EXIT_H_ */