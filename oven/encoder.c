#include "common.h"
#include "timer.h"


int8_t check(){
	if(!((PINB & (1 << 3)) && (PINB & (1 << 4)))){
		if(!(PINB & (1 << 3))){
			while(!(PINB & (1 << 3) && PINB & (1 << 4)));
			_delay_loop_2(5000);
			return 1;
		} else {
			while(!(PINB & (1 << 3) && PINB & (1 << 4)));
			_delay_loop_2(5000);
			return -1;
		}
	}
	return 0;
}

int8_t going(){
	timerReset();
	int8_t i = 0;
	while(Time() < 35 )
		i += check();
	
	if(i >= 2)
		return 1;
	else if(i <= -2)
		return -1;
	else 
		return 0;	
}