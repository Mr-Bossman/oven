#include <avr/io.h>
#define F_CPU 8000000UL
#include "util/delay.h"

#include "timer.h"
#include "lcd.h"
#include "ascii.h"

int main(void)
{
	lcdbegin(16,2);
	Cprint(lcdwrite,"Hello world!");
	initTime();
	sei();
	while (1)
	{
		lcdsetCursor(0,1);
		unsigned char* arr = NULL;
		print(lcdwrite,arr,int8_2_char(&arr,(Time()/1000)));
		free(arr);
		

	}
}
