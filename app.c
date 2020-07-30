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
int main()
{
	xqUartInit(9600);
	xqSpiInit(XQ_SPI_MODE_MASTER);
	xqSpiAddSlave(SPI_SS);

	int i=0;
	unsigned char c;
	while(1){
		if(i%2==0){
			c = 0xFF;
		}else{
			c = 0x00;
		}
		xqSpiEnableSlave(SPI_SS);
		c = xqSpiTransferByte(c);
		xqSpiDisableSlave(SPI_SS);

		xqUartSendByte(c);
		i++;
		_delay_ms(1000);
	}
	return 0;
}
