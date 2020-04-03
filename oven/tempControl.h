#ifndef TEMPCONTROL_H
#define TEMPCONTROL_H
#include "commonH.h"
#include "timer.h"
typedef struct TEMPOP{
	uint16_t Time;
	uint16_t temp;
	uint8_t margin;
	bool DPS;
}TEMPOP;
extern void temps(TEMPOP temp);
#endif