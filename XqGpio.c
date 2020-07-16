#include "XqGpio.h"
#include <avr/io.h>

static int 
find_pin(unsigned char pin, char* pPort, unsigned char* pPin)
{
	if(pin>=0 && pin<=7){
		*pPort = 'D';
		*pPin = pin;
	}else if(pin>=8 && pin<=13){
		*pPort = 'B';
		*pPin = pin-8;
	}else if(pin>A0 && pin<=A5){
		*pPort = 'C';
		*pPin = pin-A0;
	}else{
		*pPort = 0;
		*pPin = -1;
		return 1;
	}
	return 0;
}

void xqGpioSetMode(unsigned char _pin, unsigned char  mode)
{
	char port = 0;
	unsigned char pin = -1;
	if(0 != find_pin(_pin, &port, &pin)){
		return;
	}
	if(mode == OUT){
		if(port == 'B'){
			DDRB |= (1<<pin);
		}else if(port == 'C'){
			DDRC |= (1<<pin);
		}else if(port == 'D'){
			DDRD |= (1<<pin);
		}
	}else{
		if(port == 'B'){
			PORTB |= (1<<pin);/* activate pull up resister */
			DDRB &= ~(1<<pin); 
		}else if(port == 'C'){
			PORTC |= (1<<pin);
			DDRC &= ~(1<<pin);
		}else if(port == 'D'){
			PORTD |= (1<<pin);
			DDRD &= ~(1<<pin);
		}
	}
}
void xqGpioWrite(unsigned char _pin, unsigned char level)
{
	char port = 0;
	unsigned char pin = -1;
	if(0 != find_pin(_pin, &port, &pin)){
		return;
	}
	if(port == 'B'){
		if(level == HIGH){
			PORTB |= (1<<pin);
		}else{
			PORTB &= ~(1<<pin);
		}
	}else if(port == 'C'){
		if(level == HIGH){
			PORTC |= (1<<pin);
		}else{
			PORTC &= ~(1<<pin);
		}
	}else if(port == 'D'){
		if(level == HIGH){
			PORTD |= (1<<pin);
		}else{
			PORTD &= ~(1<<pin);
		}
	}else{
		return;
	}

}
unsigned char xqGpioRead(unsigned char _pin)
{
	char port = 0;
	unsigned char pin = -1;
	if(0 != find_pin(_pin, &port, &pin)){
		return 0;
	}
	if(port == 'B'){
		return (PINB & (1<<pin))?1:0;
	}else if(port == 'C'){
		return (PINC & (1<<pin))?1:0;
	}else if(port == 'D'){
		return (PIND & (1<<pin))?1:0;
	}else{
		return 0;
	}
}
