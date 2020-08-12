#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "XqGpio.h"
#include <avr/interrupt.h>

typedef struct Servo {
	unsigned char pin;
	unsigned int duty_clicks;
	unsigned int cycle_clicks; 
	unsigned int clicks;
}Servo;

/* 18 pins for servos: 2-13, A0-A5 */
Servo M[18];

static void on_100us();
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 231; /*256 - 160 */
	on_100us();
}

static void start_timer()
{
	TCNT0 = 231;
	TCCR0A = 0;
	TIMSK0 = (1<<TOIE0);
	TCCR0B = 0x03; /* prescal = 1 */
	sei();
}

#define US_PER_CLICK 100
static void init_servos()
{
	int i=0;
	unsigned char pins[] = {2,3,4,5,6,7,8,9,10,11,12,13,A0,A1,A2,A3,A4,A5};
	for(i=0; i<18; i++){
		M[i].pin = pins[i];
		M[i].duty_clicks = 500 / US_PER_CLICK;
		M[i].cycle_clicks = 2000 / US_PER_CLICK;
		M[i].clicks = 0;
		xqGpioSetMode(M[i].pin, OUT);
	}
}
static void on_100us()
{
	int i;
	for(i=0; i<17; i++){
		if(M[i].clicks == 0){
			xqGpioWrite(M[i].pin, HIGH);
		}
		if(M[i].clicks == M[i].duty_clicks){
			xqGpioWrite(M[i].pin, LOW);
		}
		M[i].clicks ++;	
		if(M[i].clicks == M[i].cycle_clicks){
			M[i].clicks = 0;
		}
	}
}


int main()
{
	init_servos();
	start_timer();

	/* start_listen */
	int i=0; 
	for(i=0;i<18;i++){
		M[i].duty_clicks = 5;
	}
	while(1)
	{
		/* start_listen */
		int i=0; 
		for(i=0;i<18;i++){
			M[i].duty_clicks = 500/US_PER_CLICK;
		}
		xqGpioWrite(A5, HIGH);
		_delay_ms(1000);
		for(i=0;i<18;i++){
			M[i].duty_clicks = 1400/US_PER_CLICK;
		}
		xqGpioWrite(A5, LOW);
		_delay_ms(1000);
		for(i=0;i<18;i++){
			M[i].duty_clicks = 24/US_PER_CLICK;
		}
		xqGpioWrite(A5, HIGH);
		_delay_ms(1000);
		xqGpioWrite(A5, LOW);
		_delay_ms(1000);
	}

	return 0;
}
