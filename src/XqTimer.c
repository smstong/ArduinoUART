#include "XqTimer.h"
#include <avr/interrupt.h>

static XqTimerCb on_timer = (void*)0;

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;
	if(on_timer){
		on_timer();
	}
}

/********************* API section ****************************/
void xqTimerInit(XqTimerCb cb)
{
	on_timer = cb;
	TCNT0 = 6;		/* (256 - 6) * 64 = 16000 clk = 1 ms */
	TCCR0A = 0x0;
	TIMSK0 = (1<<TOIE0);
	TCCR0B = 0x00;	/* timer is stopped */
	sei();
}
void xqTimerStart()
{
	TCCR0B = 0x03; /* clk / 64 */
}
void xqTimerStop()
{
	TCCR0B = 0x00;
}
