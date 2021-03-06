#include "MAX31855.h"

uint16_t sence_temp = 0;
uint16_t sence_temp_internal = 0;

static uint32_t spi(){
	PORTC &= ~(1 << 5);
	_delay_ms(1);
	uint32_t ret = 0;
	for(uint8_t i = 0;i < 32; i++){
		PORTE |= (1 << 2); // 100ns delays between each instruction
		_delay_loop_1(10);
		ret <<= 1;
		ret |= (PINC >> 4) & 1;
		PORTE &= ~(1 << 2);
		_delay_loop_1(10);
	}
	_delay_ms(1);
	PORTC |= (1 << 5);
	_delay_ms(1);
	return ret;
}

bool update_temp(){ //returns true if somthing went wrong	
	uint32_t dat = spi();
	sence_temp = (dat >> 18);
	sence_temp_internal = (dat >> 4)&0xfff;
	return ((dat >> 16) & 1);
	
}