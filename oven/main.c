#include <avr/io.h>
#include "avr/interrupt.h"

#include "commonH.h"
#include "UI.h"

#include "timer.h"
#include "tempControl.h"
#include "lcd.h"
#include "ascii.h"
#include "analog.h"
int main(void)
{
	lcdbegin(16,2);
	ADCInit();
	initTime();
	sei();
	beginUI();

	while (1)
	{
		lcdsetCursor(0,1);
		unsigned char arr[16];
		memset(arr,254,16);
		arr[int16_2_char(arr,(uint16_t)(Time()/1000))] = 223;
		arr[int16_2_char(&arr[6],readADC(0))+6] = 223;
		print(lcdwrite,arr,16);
		

	}
}
