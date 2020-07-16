#Arduino Drivers

## GPIO driver
### Usage
	#include "XqGpio.h"
	
	xqGpioSetMode(8, OUT);
	xqGpioWrite(8, HIGH);

	xqGpioSetMode(A0, IN);
	unsigned char level = xqGpioRead(A0);

## LCD driver
### Usage
	#include "XqLcd.h"	 
	
	XqLCD lcd1;
	xqLcdInit(&lcd1, 2, 16, 13, 12, 11, 7, 6, 5, 4);
	xqLcdWriteMsg(&lcd1, "hello", 4);

## Interrupt-based UART driver
### How to use it for send data via UART?

	#include "XqUart.h"
	
	xqUartInit(9600);
	xqUartSendMsg("Hello", 5);
  
### How to use it for receive data via UART?

	#include "XqUart.h"
	
	void OnByteRecv(unsigned char c)
	{
		/* do something */
	}
	
	xqUartInit(9600);
	xqUartSetByteRecvCb(OnByteRecv);
	
