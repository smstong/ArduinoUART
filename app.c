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

XqKb kb1;

void uart_cb(unsigned char c)
{
	xqUartSendByte(c);
}

int main()
{
	xqUartInit(9600);
	xqUartSetByteRecvCb(uart_cb);

	unsigned char rowPins[] = {9,8,7,6};
	unsigned char colPins[] = {5,4,3,2};
	char keyMaps[] = {
		'1', '2', '3', 'A', 
		'4', '5', '6', 'B',
		'7', '8', '9', 'C',
		'*', '0', '#', 'D',
	};
	
	xqKbInit(&kb1, rowPins, colPins, 
			&keyMaps[0], 
			sizeof(rowPins)/sizeof(rowPins[0]),
			sizeof(colPins)/sizeof(colPins[0]));

	int i=0;
	for(i=0; i<10; i++){
		xqUartSendByte(xqKbGetKey(&kb1));
	}	

	return 0;
	}
