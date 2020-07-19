#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "XqUart.h"
#include "XqLcd.h"
#include "XqGpio.h"
#include "XqKb.h"
#include "XqAdc.h"
#include "XqStepMotor.h"
#include <avr/interrupt.h>


void uart_cb(unsigned char c)
{
	xqUartSendByte(c);
}
static int duty_percent = 100;
void clock_wise();
void ccw();
void on_second()
{
	static unsigned int s = 0;
	if(s % 10 == 0){
		clock_wise();
	}else if(s % 5 == 0){
		ccw();
	}
	s++;
}
void on_ms()
{
	static unsigned ms = 0;
	static int i = 1;
	if(i==1){
		xqGpioWrite(A5, HIGH);
	}
	if(i==duty_percent) {
		xqGpioWrite(A5, LOW);
	}
	if(++i==100){
		i=1;
	}
	
	ms++;
	if(ms % 1000 == 0){
		on_second();
	}
}


void A2_ready(unsigned int r)
{
	duty_percent = (int)(100.0 * r / 1023.0);
	char msg[16]={0};
	sprintf(msg, "duty cycle: %d\r\n", duty_percent);
	xqUartSendStr(msg);
}

void clock_wise()
{
	xqGpioWrite(2, LOW);
	xqGpioWrite(3, HIGH);
	xqGpioWrite(4, HIGH);
	xqGpioWrite(5, LOW);
}

void ccw()
{
	xqGpioWrite(2, HIGH);
	xqGpioWrite(3, LOW);
	xqGpioWrite(4, LOW);
	xqGpioWrite(5, HIGH);
}

int main()
{
	xqUartInit(9600);
	xqUartSetByteRecvCb(uart_cb);

	xqTimerInit(on_ms);
	xqTimerStart();

	xqAdcInit();
	xqAdcAdd(A2, 1, A2_ready);
	xqAdcStart();

	xqGpioSetMode(A0, OUT); // A0 for 1_2_EN
	xqGpioWrite(A0, HIGH);


	xqGpioSetMode(A5, OUT);	// A5 for INPUT
	xqGpioWrite(A5, HIGH);

	xqGpioSetMode(2, OUT); // Relay, Yellow
	xqGpioSetMode(3, OUT); // Relay, Orange
	xqGpioSetMode(4, OUT); // Relay, Blue
	xqGpioSetMode(5, OUT); // Relay, Black

	xqGpioWrite(2, HIGH);
	xqGpioWrite(3, HIGH);
	xqGpioWrite(4, HIGH);
	xqGpioWrite(5, HIGH);

	while(1);
	return 0;
}
