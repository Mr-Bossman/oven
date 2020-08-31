#include "common.h"
#include "timer.h"

#define ERROR_MARGIN 5

static uint16_t get_temp(){
	return 100;
}
static uint16_t set_temp(uint16_t C){
	uint16_t temp = get_temp(); // need to add get temp function
	if(((temp>C)?temp-C:C-temp) > ERROR_MARGIN){ // need to add error statement 
		if(temp>C){
			//set off 
		} else {
			//set on
		}
	}
	return temp;
}

extern void update(uint32_t* data,	void (*screen)(bool,uint16_t,uint16_t)){ //rising or stable temp and time
	for(uint8_t i = 0; i < 6;i++){
		if(data[i] == 0)break;
		if(((uint16_t*)&data[i])[1]& (1<<15)){
			timerReset();
			uint32_t T = ((uint32_t)(((uint16_t*)&data[i])[1]& ~(1<<15)))*1000;// need to be fiuxed
			while(Time()<T){
				screen(1,set_temp(((uint16_t*)&data[i])[0]),(T-Time())/1000);// need to be fiuxed
			}
		} else {// value is 500 to -500 and is realy 5 to -5 deg c /s		
			uint16_t last = get_temp();
			timerReset();
			uint32_t T = ((uint32_t)(((uint16_t*)&data[i])[1]& ~(1<<15)))*1000;// need to be fiuxed
			while(Time()<T){
				if(Time()%100 == 0){
					last += ((uint16_t*)&data[i])[1] & ~(1<<15);// adds // need to be fiuxed
				}
				screen(0,set_temp(last),(T-Time())/1000);
			}
		}
	}
}