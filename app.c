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
#include "XqSpi.h"
#include "XqVirtualUart.h"
#include <avr/interrupt.h>
#include "XqI2c.h"

#define SPI_CLK 13
#define SPI_MISO 12
#define SPI_MOSI 11
#define SPI_SS 10
XqVirtualUart s0;

unsigned char spi_bitbang_byte(unsigned char byte_out)
{
	unsigned char byte_in = 0;
	unsigned char bit;
	for(bit = 0x80; bit; bit >>= 1){
		xqGpioWrite(SPI_MOSI, (byte_out & bit) ? HIGH : LOW);
		_delay_ms(50);
		xqGpioWrite(SPI_CLK, HIGH);
		if(xqGpioRead(SPI_MISO)) {
			byte_in |= bit;
		}
		_delay_ms(100);
		xqGpioWrite(SPI_CLK, LOW);
	}
	return byte_in;
}

void rtc_setTime(unsigned char h, unsigned char m, unsigned char s)
{
	xqI2cStart();
	xqI2cWriteByte(0xD0);
	xqI2cWriteByte(0x00);
	xqI2cWriteByte(s);
	xqI2cWriteByte(m);
	xqI2cWriteByte(h);
	xqI2cStop();
}

void rtc_setDate(unsigned char y, unsigned char m, unsigned char d,
		unsigned char dow)
{
	xqI2cStart();
	xqI2cWriteByte(0xD0);
	xqI2cWriteByte(0x03);
	xqI2cWriteByte(dow);
	xqI2cWriteByte(d);
	xqI2cWriteByte(m);
	xqI2cWriteByte(y);
	xqI2cStop();
}

void rtc_getTime(unsigned char *h, unsigned char *m, unsigned char *s)
{
	xqI2cStart();
	xqI2cWriteByte(0xD0); /* address: 1101000, op: write */
	xqI2cWriteByte(0x00); /* set register pointer to 0x00 */
	xqI2cStop();

	xqI2cStart();
	xqI2cWriteByte(0xD1); /* address: 1101000, op: read */
	*s = xqI2cReadByte(1);
	*m = xqI2cReadByte(1);
	*h = xqI2cReadByte(0);
	xqI2cStop();
}
void rtc_getDate(unsigned char* y, unsigned char *M, unsigned char *d)
{
	xqI2cStart();
	xqI2cWriteByte(0xD0);
	xqI2cWriteByte(0x04);
	xqI2cStop();

	xqI2cStart();
	xqI2cWriteByte(0xD1);
	*d = xqI2cReadByte(1);
	*M = xqI2cReadByte(1);
	*y = xqI2cReadByte(0);
	xqI2cStop();
}

void rtc_init(void)
{
	xqI2cInit();
	xqI2cStart();
	xqI2cWriteByte(0xD0);
	xqI2cWriteByte(0x07);
	xqI2cWriteByte(0x00);
	xqI2cStop();
}

void uart_send_bcd(XqVirtualUart* s, unsigned char bcd)
{
	xqVirtualUartSendByte(s, '0' + (bcd >> 4)); /* 10x */
	xqVirtualUartSendByte(s, '0' + (bcd & 0x0F)); /* 1x */
}
void uart_send_str(XqVirtualUart* s, const char* str)
{
	const char* p = NULL;
	for(p=str; *p; p++){
		xqVirtualUartSendByte(s, *p); 
	}
}
int main()
{
	xqVirtualUartInit(&s0, 9, 8, 9600);

	rtc_init();
	//rtc_setTime(0x02, 0x33, 0x00);
	//rtc_setDate(0x20, 0x08, 0x04, 0x2);

	while(1){
		unsigned char hour, min, second;
		unsigned char year, mon, day;

		rtc_getDate(&year, &mon, &day);
		uart_send_str(&s0, "current time: ");
		uart_send_str(&s0, "20");
		uart_send_bcd(&s0, year);
		xqVirtualUartSendByte(&s0, '-');
		uart_send_bcd(&s0, mon);
		xqVirtualUartSendByte(&s0, '-');
		uart_send_bcd(&s0, day);

		uart_send_str(&s0, "  ");

		rtc_getTime(&hour, &min, &second);
		uart_send_bcd(&s0, hour);
		xqVirtualUartSendByte(&s0, ':');
		uart_send_bcd(&s0, min);
		xqVirtualUartSendByte(&s0, ':');
		uart_send_bcd(&s0, second);
		uart_send_str(&s0, "\r\n");

		_delay_ms(1000);
	}
	return 0;
}
