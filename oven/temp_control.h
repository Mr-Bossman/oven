/*
 * temp_control.h
 *
 * Created: 8/24/2020 6:09:37 PM
 *  Author: jesse
 */ 
#include "common.h"

#ifndef TEMP_CONTROL_H_
#define TEMP_CONTROL_H_

struct tempC {
	bool stableTemp;
	uint16_t temp;
	uint16_t times;
	int16_t rise;

};
uint16_t get_temp();
void update(struct tempC * data, void (*screen)(struct tempC)); //rising or stable temp and time



#endif /* TEMP_CONTROL_H_ */