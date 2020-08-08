#include "XqServo.h"
#include "XqGpio.h"
#include "XqTimer.h"

static void on_click(void* arg)
{
	XqServo* m = (XqServo*)arg;
	if(m->clicks == 0){
		xqGpioWrite(m->pinPWM, HIGH);
	}
	if(m->clicks == m->duty_clicks){
		xqGpioWrite(m->pinPWM, LOW);
	}

	m->clicks++;
	if(m->clicks == m->cycle_clicks) {
		m->clicks = 0;
	}
}

/**************** API seciton **********************/
void xqServoInit(XqServo* m, unsigned char pinPWM)
{
	m->angle = 0;
	m->duty_min_us = 500;
	m->duty_max_us = 2400;
	m->cycle_us = 20000;

	m->clicks_per_us = 100; /* 100us timer */

	m->cycle_clicks = m->cycle_us / m->clicks_per_us;
	m->duty_clicks = m->duty_min_us / m->clicks_per_us;

	m->pinPWM = pinPWM;
	xqGpioSetMode(pinPWM, OUT);
	m->clicks = 0;

	xqTimerAddCb(on_click, m);
}
/* angle: 0-180 */
void xqServoSetPos(XqServo* m, float angle)
{
	float duty_us = m->duty_min_us + 
		(angle/180.0)*(m->duty_max_us - m->duty_min_us);
	m->angle = angle;	
	m->duty_clicks = (unsigned int)(duty_us / m->clicks_per_us);
}

float xqServoGetPos(XqServo* m)
{
	return m->angle;
}
