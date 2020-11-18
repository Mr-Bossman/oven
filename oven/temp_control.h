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
};
void update(struct tempC* data,	void (*screen)(bool,uint16_t,uint16_t,uint16_t)); //rising or stable temp and time



#endif /* TEMP_CONTROL_H_ */