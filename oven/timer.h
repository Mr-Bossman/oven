
#ifndef TIMER_H_
#define TIMER_H_
#include "common.h"
#ifndef  interrupt_h__
#include "avr/interrupt.h"
#endif
void initTime();
uint32_t Time();

void timerReset();


#endif 