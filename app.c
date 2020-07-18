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

XqStepMotor m1;

void uart_cb(unsigned char c)
{
	xqUartSendByte(c);
}
void on_second(unsigned int seconds)
{
	if(seconds % 5 == 0){
		xqStepMotorSetDir(&m1, -xqStepMotorGetDir(&m1));
	}	
}
void on_ms()
{
	static unsigned int ms = 0;
	static unsigned int seconds = 0;

	if(ms % 1000 == 0){
		seconds ++;
		on_second(seconds);
	}
	if(ms % 2 == 0){
		xqStepMotorStep(&m1);
	}
	ms ++;
}

int main()
{
	xqUartInit(9600);
	xqUartSetByteRecvCb(uart_cb);

	xqStepMotorInit(&m1, 8,9,10,11);

	xqTimerInit(on_ms);
	xqTimerStart();

	while(1);
	return 0;
}
