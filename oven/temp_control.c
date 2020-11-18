#include "common.h"
#include "timer.h"
#include "MAX31855.h"
#include "temp_control.h"


#define ERROR_MARGIN 5

static uint16_t get_temp(){ //get temp has 2 fixed point paces of persision 
	if(update_temp());// exit(0); // bruh u ducked up
	//if (sence_temp_internal > 80) exit(0); //bruh its hot in here
	return sence_temp;
}
static uint16_t set_temp(uint16_t C){ // set temp has 2 fixed point paces of persision 
	uint16_t temp = get_temp(); // need to add get temp function
	if(((temp>C)?temp-C:C-temp) > ERROR_MARGIN){ // need to add error statement 
		if(temp>C){
			PORTC &= ~(4);
		} else {
			PORTC |= 4;
		}
	}
	return temp;
}

void update(struct tempC* data, void (*screen)(bool,uint16_t,uint16_t,uint16_t)){ //rising or stable temp and time
	for(uint8_t i = 0; i < 6;i++){
		if(data[i].temp == 0)break;
		if(data[i].stableTemp){
			timerReset();
			uint32_t T = data[i].times * 1000;
			while(Time()<T){
				screen(1,(set_temp(data[i].temp << 2) >> 2),data[i].temp ,(T-Time())/1000); // shift by 2 becuse set temp has 2 fixed point paces of persision 
			}
		} else { // value is 500 to -500 and is realy 5 to -5 deg c /s		
			uint16_t last = get_temp();
			timerReset();
			uint32_t T = data[i].times * 1000;
			while(Time()<T){
				if(Time()%500 <= 20){
					if(get_temp() < last+(data[i].temp/50)){ // 100/4=25  100 is one deg on data.temp and 4 is one deg on the  sensor every haf a second we check so we mult by 2
						PORTC |= 4;
					}else {
						PORTC &= ~(4);
					}
					last += data[i].temp/50;
					_delay_loop_2(20000);
				}
				screen(0,(get_temp() >> 2),(last>>2) ,(T-Time())/1000);
			}
		}
	}
}