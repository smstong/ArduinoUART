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
#include "XqD7.h"
#include <avr/interrupt.h>


XqD7 d1;
char buf[] = {'0', '0', '0', '0', '0'};
void i2a(int x, char buf[])
{
	if(x<0){
		x = -x;
	}
	int i=0;
	while(x){
		buf[i++] = 0x30 + (x % 10);
		x = x / 10;
	}
}
void display(int ms)
{
	static int i=0;
	xqD7Write(&d1, i,buf[3-i]); 
	i++;
	if(i>=4) i=0;
}
void uart_cb(unsigned char c)
{
	xqUartSendByte(c);
}
void on_second()
{
	static unsigned int s = 0;
	s++;
	i2a(s, buf);
}
void on_ms()
{
	static unsigned ms = 0;
	ms++;
	if(ms % 100 == 0){
		on_second();
	}
	if(ms % 5 == 0){
		display(ms/5);
	}
}

int main()
{
	xqUartInit(9600);
	xqUartSetByteRecvCb(uart_cb);

	xqTimerInit(on_ms);
	xqTimerStart();

	unsigned char selPin[] = {A1,A2,A3,A4};
	xqD7Init(&d1, 6,7,8,9,10,11,12,13, selPin, 4);
	xqD7Write(&d1, 0, '3');
	xqD7Write(&d1, 1, '3');

	while(1);
	return 0;
}
