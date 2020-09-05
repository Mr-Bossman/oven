#include "common.h"
#include "timer.h"
#include "MAX31855.h"


#define ERROR_MARGIN 5

static uint16_t get_temp(){
	if(update_temp());// exit(0); // bruh u ducked up
	//if (sence_temp_internal > 80) exit(0); //bruh its hot in here
	return sence_temp;
}
static uint16_t set_temp(uint16_t C){
	uint16_t temp = get_temp(); // need to add get temp function
	if(((temp>C)?temp-C:C-temp) > ERROR_MARGIN){ // need to add error statement 
		if(temp>C){
			PORTC &= ~(2);
		} else {
			PORTC |= 2;
		}
	}
	return temp;
}

void update(uint32_t* data, void (*screen)(bool,uint16_t,uint16_t,uint16_t)){ //rising or stable temp and time
	for(uint8_t i = 0; i < 6;i++){
		if(data[i] == 0)break;
		if(data[i] & ( 1ul << 31)){
			timerReset();
			uint32_t T = ((data[i] & ~( 1ul << 31)) >> 16)*1000;// need to be fiuxed
			while(Time()<T){
				screen(1,(set_temp((data[i]&0xffff) << 2) >> 2),(data[i]&0xffff) ,(T-Time())/1000);
			}
		} else { // value is 500 to -500 and is realy 5 to -5 deg c /s		
			uint16_t last = get_temp();
			timerReset();
			uint32_t T = ((data[i] & ~( 1ul << 31)) >> 16)*1000;
			while(Time()<T){
				if(Time()%100 == 0){
					last += data[i] ;//  need to be fiuxed // need to covert here un known maths
				}
				screen(0,(set_temp(last) >> 2),(data[i]&0xffff) ,(T-Time())/1000);
			}
		}
	}
}