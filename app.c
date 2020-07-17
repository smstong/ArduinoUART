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


void uart_cb(unsigned char c)
{
	xqUartSendByte(c);
}

void A0_ready(unsigned int r)
{
	char msg[16];
	sprintf(msg, "A0: %d\r\n", r);
	xqUartSendStr(msg);
}

void A5_ready(unsigned int r)
{
	char msg[16];
	sprintf(msg, "A5: %d\r\n", r);
	xqUartSendStr(msg);
}
void A2_ready(unsigned int r)
{
	char msg[16];
	sprintf(msg, "A2: %d\r\n", r);
	xqUartSendStr(msg);
}

int main()
{
	xqUartInit(9600);
	xqUartSetByteRecvCb(uart_cb);

	xqAdcInit();
	xqAdcAdd(A0, 1, A0_ready); 
	xqAdcAdd(A5, 1, A5_ready); 
	xqAdcAdd(A2, 1, A2_ready); 
	xqAdcStart();


	while(1);
	return 0;
}
