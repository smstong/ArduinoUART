#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include "XqVirtualUart.h"
#include "XqDs1307.h"
#include "XqTimer.h"
#include "XqGpio.h"
#include "XqAdc.h"
#include "XqTimer.h"
#include "XqServo.h"

XqVirtualUart s0;
XqServo m1;
XqServo m2;
XqServo m3;

void print(const char* str)
{
	const char* p = NULL;
	for(p=str; *p; p++){
		xqVirtualUartSendByte(&s0, *p); 
	}
}

int main()
{
	xqVirtualUartInit(&s0, 9, 8, 9600);
	xqServoInit(&m1, 6);
	xqServoInit(&m2, 5);
	xqServoInit(&m3, 2);

	xqTimerStart();

	float angle = 0;
	while(1){
		xqServoSetPos(&m1, angle);
		xqServoSetPos(&m2, angle);
		xqServoSetPos(&m3, angle);
		_delay_ms(100);
		angle += 10.0;
		if(angle >180){
			angle = 0;
		}

	}
	return 0;
}
