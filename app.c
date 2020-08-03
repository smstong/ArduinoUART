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

#define SPI_CLK 13
#define SPI_MISO 12
#define SPI_MOSI 11
#define SPI_SS 10

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

XqVirtualUart s0;
int main()
{
	xqVirtualUartInit(&s0, 9, 8, 9600);
	while(1){
		unsigned char byte_in = xqVirtualUartRecvByte(&s0);
		xqVirtualUartSendByte(&s0, byte_in);
	}
	return 0;
}
