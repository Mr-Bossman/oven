#include "tempControl.h"
static void temp4Time(TEMPOP timedHeat);
static uint16_t setTemp(TEMPOP heat);
static void riseTemp4Time(TEMPOP timedHeat);
extern void temps(TEMPOP temp) {
	if(temp.DPS){
		riseTemp4Time(temp);
		}else {
		temp4Time(temp);
	}
}
static void temp4Time(TEMPOP timedHeat){
	timerReset();
	while(Time() < timedHeat.Time){
		setTemp(timedHeat);
	}
}
static uint16_t setTemp(TEMPOP heat){
	uint16_t currentTemp = 0;
	if(heat.temp > currentTemp+heat.margin){
		PORTB |= (1<<5);
		}  else if(heat.temp < currentTemp-heat.margin){
		PORTB &= ~(1<<5);
	}
	return currentTemp;
}
static void riseTemp4Time(TEMPOP timedHeat){ //time is used for deg per 100ms
	uint16_t endTemp = timedHeat.temp;
	uint16_t startTemp = 0;
	for(uint16_t i = startTemp; i < endTemp;i += timedHeat.Time){
		timedHeat.temp = i;
		timerReset();
		while(Time() < 100){
			setTemp(timedHeat);
		}
	}
}
