# Arduino Drivers

This repo is a collection C libs written for Arduino Uno R3 when I learn it.
Arduino IDE/API is NOT used, while avr-as/avr-gcc/avrdude are used directly.

Development Env:

* OS: CentOS7
* Assembler: avr-as
* C compiler: avr-gcc
* Programmer: avrdude
* Hardware: Arduino Uno R3

Learn Arduino the harder way.
Learn Arduino from the scratch.
Learn Arduino with Assebly and C.

## DS1307 RTC driver
### Usage
	#include "XqDs1307.h"
	
	unsigned char hour, min, second;
	unsigned char year, mon, day, dow;
	
	xqDs1307Init();
	xqDs1307SetTime(20,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF);
	xqDs1307GetTime(&year, &mon, &day, &dow, &hour, &min, &second);


## I2C driver
### Usage
	#include "XqI2c.h"
	
	xqI2cInit();

	xqI2cStart();
	xqI2cWriteByte(0xD0);
	xqI2cWriteByte(0x00);
	xqI2cStop();
	
	xqI2cStart();
	xqI2cWriteByte(0xD1);
	xqI2cReadByte(1);
	xqI2cReadByte(1);
	xqI2cReadByte(0);
	xqI2cStop();

## Virtual UART driver
### Usage
	#include "XqVirtualUart.h"	

	XqVirtualUart s0;
	int main()
	{
		xqVirtualUartInit(&s0, 9, 8, 9600); /* Tx: pin 9, Rx: pin 8 */
		while(1){
			unsigned char byte_in = xqVirtualUartRecvByte(&s0);
			xqVirtualUartSendByte(&s0, byte_in);
		}
		return 0;
	}

## SPI driver
### Usage
	#include "XqSpi.h"
	
	unsigned char pin_slave_1 = 8;
	unsigned char byte_out = 'O';
	unsigned char byte_in;	
	
	xqSpiInit(XQ_SPI_MODE_MASTER);
	xqSpiAddSlave(pin_slave_1);
	
	xqSpiEnableSlave(pin_slave_1);
	
	byte_in = xqSpiTransferByte(byte_out);
	
	xqSpiDisableSlave(pin_slave_1);

## 7-segments display driver
### Usage
	#include "XqD7.h"
	
	XqD7 display1;
	
	unsigned char selPin[] = {A1,A2,A3,A4};
	xqD7Init(&d1, 6,7,8,9,10,11,12,13, selPin, 4);
	xqD7Write(&display1, 0, '3');

## Stepper motor driver
### Usage

	#include "XqStepMotor.h"
	
	XqStepMotor m1;
	
	xqStepMotorInit(&m1, 2,3,4,5);
	xqStepMotorSetDir(&m1, -1);

	/* go one step */
	xqStepMotorStep();
	

## 1ms Timer driver
### Usage
	#include "XqTimer.h"
	
	void on_timer(void* arg)
	{
		/* run something every 100 us here */
	}
	
	xqTimerAddCb(on_timer, NULL);

	xqTimerStart();
	
## ADC driver
### Usage
	#include "XqAdc.h"
	
	void A0_ready(unsigned int r)
	{
		/* do anything with r */
	}
	xqAdcInit();
	xqAdcAdd(A0, 1, A0_ready); 
	xqAdcStart();

## KeyBoard driver
### Usage
	#include "XqKb.h"
	
	XqKb kb1;
	unsigned char rowPins[] = {9,8,7,6};
	unsigned char colPins[] = {5,4,3,2};
	char keyMaps[] = {
		'1', '2', '3', 'A', 
		'4', '5', '6', 'B',
		'7', '8', '9', 'C',
		'*', '0', '#', 'D',
	};

	xqKbInit(&kb1, rowPins, colPins, 
			&keyMaps[0], 
			sizeof(rowPins)/sizeof(rowPins[0]),
			sizeof(colPins)/sizeof(colPins[0]));

	...
	char c = xqKbGetKey(&kb1);
	...

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
	
