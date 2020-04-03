#ifndef TIMER_H
#define TIMER_H
#include "commonH.h"
#ifndef F_CPU
# warning "F_CPU not defined for timer.h"
# define F_CPU 16000000UL
#endif

#define milli (uint16_t)(F_CPU/1000)
//inits the library on timer 1
extern void initTime();
//retuns milliseconds
extern uint32_t Time();
// resets the timer
extern void timerReset();
#endif