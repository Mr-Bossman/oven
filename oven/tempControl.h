#ifndef TEMPCONTROL_H
#define TEMPCONTROL_H
#include <stdbool.h>
#include <avr/io.h>
#include "timer.h"
typedef struct TEMPOP{
	uint16_t Time;
	uint16_t temp;
	uint8_t margin;
	bool DPS;
}TEMPOP;
extern void temps(TEMPOP temp);
static void temp4Time(TEMPOP timedHeat);
static uint16_t setTemp(TEMPOP heat);
static void riseTemp4Time(TEMPOP timedHeat);
#endif