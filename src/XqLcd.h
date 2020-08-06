/***************************************************************
 * 16-pin LCD Driver
 * 
 * Hardware connection:
 *
 * LCD       	Arduino
 * RS	<----> pin_RS
 * RW 	<----> pin_RW
 * EN	<----> pin_EN
 * D7	<----> pin_D7
 * D6	<----> pin_D6
 * D5	<----> pin_D5
 * D4	<----> pin_D4
 * VDD  <----> +5V
 * A	<----> +5V
 * K	<----> GND
 * Vss	<----> GND
 *
 * ************************************************************/
#ifndef XQ_LCD_H
#define XQ_LCD_H
typedef struct XqLcd 
{
	unsigned char rows;
	unsigned char cols;
	unsigned char pin_RS; 
	unsigned char pin_RW; 
	unsigned char pin_EN;
	unsigned pin_D7; 
	unsigned pin_D6; 
	unsigned pin_D5; 
	unsigned pin_D4;
	unsigned char curX; /* cursor pos */
	unsigned char curY;
}XqLcd;

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
		unsigned pin_D4);

/* Move cursor to (col, row). Both start from 1 */
void xqLcdMoveTo(XqLcd* lcd, unsigned char col, unsigned char row);

/* write a char at current cursor position */
void xqLcdWriteByte(XqLcd* lcd, char c);

/* write len chars starting at current cursor position */
void xqLcdWriteMsg(XqLcd* lcd, char* c, int len);

/* clear all and move cursor to (1,1) */
void xqLcdClear(XqLcd* lcd);

#endif /* XQ_LCD_H */
