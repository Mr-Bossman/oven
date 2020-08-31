#include "timer.h"
#define milli (uint16_t)(F_CPU/128000)
static volatile uint32_t milliSeconds = 0;
extern void initTime(){
	sei();
	TCCR1A = 3;
	TCCR1B =  16| 3; // mode to count to ocrnA then restet // set no pre scalar 16MHZ
	OCR1A = milli; // count to  then reset this  is one milisecond
	TIMSK1 = 2; // compare interupt
   
}
//retuns milliseconds
extern uint32_t Time(){
	return milliSeconds;
}

extern void timerReset(){
	TCNT1 = 0;
	milliSeconds = 0;
}
ISR(TIMER1_COMPA_vect){
	milliSeconds++; // increnment the seconds
}