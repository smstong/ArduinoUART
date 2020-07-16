#include "XqUart.h"
#include "XqLcd.h"
#include "XqGpio.h"

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

XqLcd lcd1;

void uart_cb(unsigned char c)
{
	xqUartSendByte(c);
	if(c=='c'){
		xqLcdClear(&lcd1);
	}else{
		xqLcdWriteByte(&lcd1, c);
	}
}

int main()
{
	xqUartInit(9600);
	xqUartSetByteRecvCb(uart_cb);

	xqLcdInit(&lcd1, 2, 16, 13, 12, 11, 7, 6, 5, 4);
	xqLcdWriteMsg(&lcd1, "hello", 4);

	while(1);
	return 0;
}
