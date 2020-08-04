#include "XqI2c.h"
#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>

void xqI2cInit(void)
{
	TWSR = 0x00;
	TWBR = 0x46;
	TWCR = (1<<TWEN);
}
void xqI2cStart(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}
void xqI2cStop(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
	_delay_us(100);
}
unsigned char xqI2cReadByte(unsigned char ifAck)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (ifAck<<TWEA);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}
void xqI2cWriteByte(unsigned char byte_out)
{
	TWDR = byte_out;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}
