#include "XqSpi.h"
#include "XqGpio.h"
#include <avr/io.h>

#define SPI_PIN_CLK 	13
#define SPI_PIN_MISO	12
#define SPI_PIN_MOSI	11
#define SPI_PIN_SS		10  /* different meaning for Master and Slave */

static char spi_mode = 0;
/*********************** API section **************************/
void xqSpiInit(char mode)
{
	if(mode == XQ_SPI_MODE_MASTER) {
		xqGpioSetMode(SPI_PIN_CLK, OUT);
		xqGpioSetMode(SPI_PIN_MISO, IN);
		xqGpioSetMode(SPI_PIN_MOSI, OUT);
		/* for a master, SS pin is recommended set as OUTPUT */
		xqGpioSetMode(SPI_PIN_SS, OUT);
		SPCR = (1<<SPE) | (1<<MSTR) | (1<<SPR0); /* Fosc/16 */
	}else{
		xqGpioSetMode(SPI_PIN_CLK, IN);
		xqGpioSetMode(SPI_PIN_MISO, OUT);
		xqGpioSetMode(SPI_PIN_MOSI, IN);
		/* for a slave, SS pin is not controlled by software actually.*/
		xqGpioSetMode(SPI_PIN_SS, IN); 
		SPCR = (1<<SPE);
		mode = XQ_SPI_MODE_SLAVE;
	}
	spi_mode = mode;
}

/* as a master */
void xqSpiAddSlave(unsigned char pinSS)
{
	if(spi_mode != XQ_SPI_MODE_MASTER){
		return;
	}
	xqGpioSetMode(pinSS, OUT);
	xqGpioWrite(pinSS, HIGH);
}
void xqSpiEnableSlave(unsigned char pinSS)
{
	if(spi_mode != XQ_SPI_MODE_MASTER){
		return;
	}
	xqGpioWrite(pinSS, LOW);
}
void xqSpiDisableSlave(unsigned char pinSS)
{
	if(spi_mode != XQ_SPI_MODE_MASTER){
		return;
	}
	xqGpioWrite(pinSS, HIGH);
}
void xqSpiSendByte(unsigned char c)
{
	SPDR = c;
	while(!(SPSR&(1<<SPIF))); /* wait until c is sent. */
}

/* as a slave */
unsigned char xqSpiRecvByte()
{
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}

