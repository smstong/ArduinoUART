#include "XqVirtualUart.h"
#include "XqGpio.h"

#define F_CPU 16000000UL
#include <util/delay.h>

#define T XqVirtualUart

/* _delay_us(compile time const) so we have this function to
 * proivde flexible delay call */
static void delay_bit(unsigned long baud)
{
	switch(baud) {
		case 1200:
			_delay_us(833 - 4); /* (1 / baud) * 1000000 - 4, (-4) for fix */
			break;
		case 2400:
			_delay_us(416 - 4);
			break;
		case 4800:
			_delay_us(208 - 4);
			break;
		case 9600:
			_delay_us(104 - 4);
			break;
		case 19200:
			_delay_us(52 - 4);
			break;
		default:
			break;
	}
}

/******************** API section ******************/
void xqVirtualUartInit(T* s, u8 pinTx, u8 pinRx, u16 baud)
{
	s->pinTx = pinTx;
	s->pinRx = pinRx;
	s->baud = baud;
	xqGpioSetMode(s->pinRx, IN);	
	xqGpioSetMode(s->pinTx, OUT);	
	xqGpioWrite(s->pinTx, HIGH);
}
void xqVirtualUartSendByte(T* s, u8 byte_out)
{
	unsigned char bit;	
	/* 1 START bit */
	xqGpioWrite(s->pinTx, LOW);
	delay_bit(s->baud);

	/* 8 bits data */
	for(bit = 0x01; bit; bit <<= 1) {
		xqGpioWrite(s->pinTx, (byte_out & bit) ? HIGH : LOW);
		delay_bit(s->baud);
	}

	/* 1 STOP bit */
	xqGpioWrite(s->pinTx, HIGH);
	delay_bit(s->baud);
}
u8 xqVirtualUartRecvByte(T* s)
{
	unsigned char bit;
	unsigned char byte_in = 0;
	while(!xqGpioRead(s->pinRx)); /* wait for STOP */
	while(xqGpioRead(s->pinRx));  /* wait for falling edge (START) */

	delay_bit(s->baud); /* START */
	delay_bit(s->baud * 2); /* half bit long */
	
	for(bit=0x01; bit; bit <<= 1){	
		if(xqGpioRead(s->pinRx)){
			byte_in |= bit;
		}
		delay_bit(s->baud);
	}
	return byte_in;
}
#undef T
