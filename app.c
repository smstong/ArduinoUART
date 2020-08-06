#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "XqVirtualUart.h"
#include <avr/interrupt.h>
#include "XqDs1307.h"

XqVirtualUart s0;

void uart_send_str(const char* str)
{
	const char* p = NULL;
	for(p=str; *p; p++){
		xqVirtualUartSendByte(&s0, *p); 
	}
}

void show_time(unsigned char year, 
		unsigned char mon, unsigned char day, unsigned char dow,
		unsigned char hour, unsigned char min, unsigned char second)
{
	char msg[32] = {0};
	sprintf(msg, "20%02d-%02d-%02d dow:%02d %02d:%02d:%02d", 
			year,mon,day,dow,hour,min,second);
	uart_send_str("current time: ");
	uart_send_str(msg);
	uart_send_str("\r\n");
}

int main()
{
	unsigned char hour, min, second;
	unsigned char year, mon, day, dow;

	xqVirtualUartInit(&s0, 9, 8, 9600);

	if(-1==xqDs1307Init()){
		uart_send_str("error: xqDs1307Init()\r\n");
	}else{
		uart_send_str("done: xqDs1307Init()\r\n");
	}
	if(-1 == xqDs1307SetTime(20,8,5,3,20,24,55)){
		uart_send_str("error: xqDs1307SetTime()\r\n");
	}else{
		uart_send_str("done: xqDs1307SetTime()\r\n");
	}

	while(1){
		if(-1 == xqDs1307GetTime(
			&year, &mon, &day, &dow, &hour, &min, &second)){
			uart_send_str("error: xqDs1307GetTime()\r\n");
		}else{
			show_time(year, mon, day, dow, hour, min, second);
		}
		_delay_ms(1000);
	}
	return 0;
}
