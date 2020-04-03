#include "timer.h"
static uint32_t milliSeconds = 0;
//inits the library on timer 1
extern void initTime(){
	TCCR1B |= (1<<3) | 1; // mode to count to ocrnA then restet // set no pre scalar
	OCR1A = ((uint16_t)milli); // count to 15625 then reset this  is one milisecond
	TIMSK1 = 2; // compare interupt
}
//retuns milliseconds
extern uint32_t Time(){
	return milliSeconds;
}
// resets the timer 
extern void timerReset(){
	TCNT1 = 0;
	milliSeconds = 0;
}
ISR(TIMER1_COMPA_vect){
	milliSeconds++; // increnment the seconds
}