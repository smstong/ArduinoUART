#include "XqI2c.h"
#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>

static char is_stopped = 0;

void xqI2cInit(void)
{
	TWSR = 0x00;
	TWBR = 0x46;
	TWCR = (1<<TWEN);
}
int xqI2cStart(void)
{
	int i=0;
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	for(i=0;i<1000;i++){
		_delay_us(100);
		if(TWCR & (1<<TWINT)){
			break;
		}
	}
	if(i==1000){
		xqI2cStop();
		return -1;
	}
	is_stopped = 0;
	return 0;
}
void xqI2cStop(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
	_delay_us(100);
	is_stopped = 1;
}
/* return 0-255  for success, -1 for error */
int xqI2cReadByte(unsigned char ifAck)
{
	if(is_stopped) return -1;
	TWCR = (1<<TWINT) | (1<<TWEN) | (ifAck<<TWEA);

	int i=0;
	for(i=0;i<1000;i++){
		_delay_us(100);
		if(TWCR & (1<<TWINT)){
			break;
		}
	}
	if(i==1000){
		xqI2cStop();
		return -1;
	}
	return TWDR;
}
/* return -1 for error */
int xqI2cWriteByte(unsigned char byte_out)
{
	if(is_stopped) return -1;
	TWDR = byte_out;
	TWCR = (1<<TWINT) | (1<<TWEN);
	int i=0;
	for(i=0;i<1000;i++){
		_delay_us(100);
		if(TWCR & (1<<TWINT)){
			break;
		}
	}
	if(i==1000){
		xqI2cStop();
		return -1;
	}
	return 0;
}
