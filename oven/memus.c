#include "common.h"
#include "timer.h"
#include "analog.h"
#include "encoder.h"
#include "lcd.h"
#include "menus.h"

/*static int8_t select(){ // how many options retuns how many to add to previos options
	/*uint16_t last =ReadADC(0);
	if(last < 50) return -1;
	if(last > 973) return 1;
	return 0;
		return going();
}
/*static uint16_t map(uint32_t x, uint32_t in_min, uint32_t in_max, uint32_t out_min, uint32_t out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
static int16_t mapadc(int32_t low,int32_t high)
{
	return ((((int32_t)usinVal()) * (high - low)) /((int32_t) 1020)) + low;
}
static uint16_t mapadcsin(uint32_t low,uint32_t high)
{
	return ((((uint32_t)usinVal()) * (high - low)) /((uint32_t) 1020)) + low;
}*/
uint8_t menu1(char str[],uint8_t options){
	int8_t pos = (options-1);
    int8_t line = 0;
	while(PINB&(1<<2)){
		int8_t tmp = going();
		if(tmp) {
				if(pos+line+tmp >= 0 && pos+line+tmp < options){
					console[pos+line][0] = ' ';
					if((line+tmp) < _numlines && (line+tmp)  >= 0) 
						line += tmp;
					else 
						pos += tmp;
					console[pos+line][0] = '>';
				} else if (pos+line+tmp == options){
					pos = (options-1);
					line = 0;
				}
		}
		lcd_print(str);
		lcd_updateScreen(pos);
	}
	while(!(PINB&(1<<2)));
	
	_delay_ms(300);
	return options-(line+pos+1);
}

uint16_t menu2(char str[],uint16_t high,uint16_t low){
	uint16_t val = 0;
	char dis[20] = {0};
	while(PINB&(1<<2)){
		val += check();
		sprintf(dis,"%s\n%u",str,val);
		lcd_print(dis);
		lcd_updateScreen(0);
		_delay_ms(10);
	}
	while(!(PINB&(1<<2)));
	
	_delay_ms(300);
	return val;
}

int16_t menu3(char str[],int16_t high,int16_t low,uint8_t place){ 
	int16_t val = 0;
	char dis[20] = {0};
	int16_t exponent = 1;
	for(uint8_t i = 0; i < place; i++) exponent *= 5 , exponent <<= 1; // ???? mult by 10 doesnt work 
	while(PINB&(1<<2)){
		val += check();
		sprintf(dis,"%s\n%d.%u",str,val/exponent,((val < 0)?-val:val)%exponent);
		lcd_print(dis);
		lcd_updateScreen(0);
		_delay_ms(10);
	}
	while(!(PINB&(1<<2)));
	
	_delay_ms(300);
	return val;
}