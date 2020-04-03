#ifndef TIMER_H
#define TIMER_H

#ifndef  _AVR_INTERRUPT_H_
#include "avr/interrupt.h"
#endif
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#define milli (uint16_t)(F_CPU/1000)

//inits the library on timer 1
extern void initTime();
//retuns milliseconds
extern uint32_t Time();
// resets the timer
extern void timerReset();
#endif