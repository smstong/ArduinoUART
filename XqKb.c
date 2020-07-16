#include "XqKb.h"
#include "XqGpio.h"
#define F_CPU 16000000UL
#include <util/delay.h>

#define debug(x) xqUartSendStr(x)

typedef unsigned char u8;

static void ground_all_rows(XqKb* kb)
{
	u8 i=0;
	for(i=0; i<kb->rows; i++){
		xqGpioWrite(kb->rowPins[i], LOW);
	}
}

static void ground_one_row(XqKb* kb, u8 row)
{
	u8 i=0;
	for(i=0; i<kb->rows; i++){
		xqGpioWrite(kb->rowPins[i], row==i?LOW:HIGH);
	}
}

/* return the low col index, or -1 if all cols are high */
static u8 find_low_col(XqKb* kb)
{
	u8 i=0;
	for(i=0; i<kb->cols; i++){
		if(!xqGpioRead(kb->colPins[i])){
			return i;
		}
	}
	return (u8)-1;
}

static void kb_scan(XqKb* kb)
{
	u8 i;
	u8 lowCol;
	ground_all_rows(kb);

	/* make sure the last pressed key has been up*/
	while((u8)-1 != (lowCol=find_low_col(kb)));

	/* wait until a key is really down for 20ms */
	while(1){
		while((u8)-1 == (lowCol=find_low_col(kb)));
		_delay_ms(20);
		if( (u8)-1 != (lowCol=find_low_col(kb))){
			break;
		}
	}

	/* find the row index */
	for(i=0; i<kb->rows; i++){
		ground_one_row(kb, i);
		lowCol = find_low_col(kb);
		if(lowCol == (u8)-1){
			/*debug("scan error\r\n");*/
		}else{
			/*find the key at (i,lowCol)*/
			if(kb->onKeyDown){
				kb->onKeyDown(*(kb->keyMaps + kb->cols*i + lowCol));
			}
		}
	}
}

/********************** API section ***************************/

void xqKbInit(XqKb* kb, 
		unsigned char *rowPins, unsigned char *colPins,
		unsigned char *keyMaps,
		unsigned char rows, unsigned char cols,
		XqKbCb cb)
{
	int i=0;

	kb->rowPins = rowPins;
	kb->colPins = colPins;
	kb->keyMaps = keyMaps;
	kb->rows = rows;
	kb->cols = cols;
	kb->onKeyDown = cb;

	for(i=0; i<rows; i++){
		xqGpioSetMode(rowPins[i], OUT);
	}
	for(i=0; i<cols; i++){
		xqGpioSetMode(colPins[i], IN);
	}

	while(1){
		kb_scan(kb);
	}
}


