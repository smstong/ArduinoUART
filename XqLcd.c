#include "XqLcd.h"
#include "XqGpio.h"
#define F_CPU 16000000UL
#include <util/delay.h>

#define T XqLcd

static void lcd_cmd(T* lcd, unsigned char cmd)
{
	xqGpioWrite(lcd->pin_D7, (cmd & (1<<7))?1:0 );	
	xqGpioWrite(lcd->pin_D6, (cmd & (1<<6))?1:0 );	
	xqGpioWrite(lcd->pin_D5, (cmd & (1<<5))?1:0 );	
	xqGpioWrite(lcd->pin_D4, (cmd & (1<<4))?1:0 );	

	xqGpioWrite(lcd->pin_RS, LOW);

	xqGpioWrite(lcd->pin_RW, LOW);
	xqGpioWrite(lcd->pin_EN, HIGH);
	_delay_us(1);
	xqGpioWrite(lcd->pin_EN, LOW);

//	_delay_us(100);

	xqGpioWrite(lcd->pin_D7, (cmd & (1<<3))?1:0 );	
	xqGpioWrite(lcd->pin_D6, (cmd & (1<<2))?1:0 );	
	xqGpioWrite(lcd->pin_D5, (cmd & (1<<1))?1:0 );	
	xqGpioWrite(lcd->pin_D4, (cmd & (1<<0))?1:0 );	

	xqGpioWrite(lcd->pin_RW, LOW);
	xqGpioWrite(lcd->pin_EN, HIGH);
	_delay_us(1);
	xqGpioWrite(lcd->pin_EN, LOW);

	if(cmd == 0x01 || cmd == 0x02){
		_delay_us(2000);
	}else{
		_delay_us(100);
	}

}
static void lcd_data(T* lcd, unsigned char data)
{
	xqGpioWrite(lcd->pin_D7, (data & (1<<7))?1:0 );	
	xqGpioWrite(lcd->pin_D6, (data & (1<<6))?1:0 );	
	xqGpioWrite(lcd->pin_D5, (data & (1<<5))?1:0 );	
	xqGpioWrite(lcd->pin_D4, (data & (1<<4))?1:0 );	

	xqGpioWrite(lcd->pin_RS, HIGH);

	xqGpioWrite(lcd->pin_RW, LOW);
	xqGpioWrite(lcd->pin_EN, HIGH);
	_delay_us(1);
	xqGpioWrite(lcd->pin_EN, LOW);

//	_delay_us(100);

	xqGpioWrite(lcd->pin_D7, (data & (1<<3))?1:0 );	
	xqGpioWrite(lcd->pin_D6, (data & (1<<2))?1:0 );	
	xqGpioWrite(lcd->pin_D5, (data & (1<<1))?1:0 );	
	xqGpioWrite(lcd->pin_D4, (data & (1<<0))?1:0 );	

	xqGpioWrite(lcd->pin_RW, LOW);
	xqGpioWrite(lcd->pin_EN, HIGH);
	_delay_us(1);
	xqGpioWrite(lcd->pin_EN, LOW);

	_delay_us(100);

}
/**************** API section *********************/
void xqLcdInit(
		XqLcd* lcd,
		unsigned char rows,
		unsigned char cols,
		unsigned char pin_RS, 
	   	unsigned char pin_RW, 
		unsigned char pin_EN,
		unsigned pin_D7, 
		unsigned pin_D6, 
		unsigned pin_D5, 
		unsigned pin_D4)
{
	lcd->rows = rows;
	lcd->cols = cols;
	lcd->pin_EN = pin_EN;
	lcd->pin_RW = pin_RW;
	lcd->pin_RS = pin_RS;
	lcd->pin_D7 = pin_D7;
	lcd->pin_D6 = pin_D6;
	lcd->pin_D5 = pin_D5;
	lcd->pin_D4 = pin_D4;
	
	xqGpioSetMode(lcd->pin_EN, OUT);
	xqGpioSetMode(lcd->pin_RS, OUT);
	xqGpioSetMode(lcd->pin_RW, OUT);
	xqGpioSetMode(lcd->pin_D7, OUT);
	xqGpioSetMode(lcd->pin_D6, OUT);
	xqGpioSetMode(lcd->pin_D5, OUT);
	xqGpioSetMode(lcd->pin_D4, OUT);

	lcd_cmd(lcd, 0x33);
	lcd_cmd(lcd, 0x32);
	lcd_cmd(lcd, 0x28);
	lcd_cmd(lcd, 0x0e);
	lcd_cmd(lcd, 0x01);
	lcd_cmd(lcd, 0x06);
	lcd_cmd(lcd, 0x80);

	lcd->curX = 1;
	lcd->curY = 1;
}

static const unsigned char firstCharAddr[] = {0x80, 0xC0, 0x94, 0xD4};
void xqLcdMoveTo(T* lcd, unsigned char col, unsigned char row)
{
	if(col>lcd->cols || row>lcd->rows) {
		return;
	}
	lcd->curX = col;
	lcd->curY = row;
	lcd_cmd(lcd, firstCharAddr[row-1] + col - 1);
}
void xqLcdWriteByte(T* lcd, char c)
{
	lcd_data(lcd, c);
	lcd->curX++;
	if(lcd->curX > lcd->cols){
		lcd->curX = 1;
		lcd->curY++;
		if(lcd->curY > lcd->rows){
			lcd->curY = 1;
		}
	}
	xqLcdMoveTo(lcd, lcd->curX, lcd->curY);
}
void xqLcdWriteMsg(T* lcd, char* msg, int len)
{
	int i = 0;
	for(i=0; i<len; i++){
		xqLcdWriteByte(lcd, msg[i]);
	}
}
void xqLcdClear(XqLcd* lcd)
{
	lcd_cmd(lcd, 0x01);
	xqLcdMoveTo(lcd, 1,1);
}
#undef T
