# Interrupt-based UART C lib for Arduino / ATmega328p 

## Development env

CentOS 7, avr-gcc

## How to use it for send data via UART?

	#include "XqUart.h"
	
	xqUartInit(9600);
	xqUartSendMsg("Hello", 5);
  
## How to use it for receive data via UART?

	#include "XqUart.h"
	
	void OnByteRecv(unsigned char c)
	{
		/* do something */
	}
	
	xqUartInit(9600);
	xqUartSetByteRecvCb(OnByteRecv);
	
