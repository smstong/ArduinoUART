#include "XqTimer.h"
#include <avr/interrupt.h>

static XqTimerCb on_timer = (void*)0;
static void* on_timer_arg = (void*)0;

struct TimerCb{
	XqTimerCb cb_f;
	void* cb_arg;
};

static struct TimerCb timer_cbs[16] = {0};

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 231; /* 256-231=25 */

	int i=0;
	for(i=0; i<(sizeof(timer_cbs)/sizeof(timer_cbs[0])); i++){
		XqTimerCb cb_f = timer_cbs[i].cb_f;
		if(cb_f){
			cb_f(timer_cbs[i].cb_arg);
		}
	}
}

static void timer_set_cb(char index, XqTimerCb cbf, void* arg)
{
	if(index<0 || (index > ((sizeof(timer_cbs))/(sizeof(timer_cbs[0]))))){
		return;
	}
	timer_cbs[index].cb_f = cbf;	
	timer_cbs[index].cb_arg = arg;
}


static timer_init()
{
	TCNT0 = 231;		/* (256 - 231) * 64 = 1600 clk = 100 us */
	TCCR0A = 0x0;
	TIMSK0 = (1<<TOIE0);
	TCCR0B = 0x00;	/* timer is stopped */
	sei();
}


/********************* API section ****************************/

/* return the index */
int xqTimerAddCb(XqTimerCb cb_f, void* cb_arg)
{
	static char i = 0;
	timer_set_cb(i, cb_f, cb_arg);
	i++;
	return i-1;
}

void xqTimerStart()
{
	timer_init();
	TCCR0B = 0x03; /* clk / 64 */
}
void xqTimerStop()
{
	TCCR0B = 0x00;
}
