
#ifndef TIMER_H_
#define TIMER_H_
#include "common.h"
#ifndef  interrupt_h__
#include "avr/interrupt.h"
#endif
extern void initTime();
extern uint32_t Time();

extern void timerReset();


#endif 