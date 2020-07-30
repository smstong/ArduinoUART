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

int main()
{
	xqUartInit(9600);
	xqSpiInit(XQ_SPI_MODE_MASTER);
	xqSpiAddSlave(8);

	int i=0;
	unsigned char c;
	while(1){
		xqSpiEnableSlave(8);
		xqUartSendStr("sending... \r\n");
		if(i%2==0){
			c = 0xFF;
		}else{
			c = 0x00;
		}
		xqSpiSendByte(c);
		xqUartSendStr("sent.\r\n");
		xqSpiDisableSlave(8);
		i++;
		_delay_ms(1000);
	}
	return 0;
}
