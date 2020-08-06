#ifndef XQ_KB_H
#define XQ_KB_H

#define XQ_KB_MAX_ROWS 8
#define XQ_KB_MAX_COLS 8

typedef struct XqKb 
{
	unsigned char *rowPins;
	unsigned char *colPins;
	unsigned char *keyMaps;
	unsigned char rows;
	unsigned char cols;

}XqKb;

void xqKbInit(XqKb* kb, 
		unsigned char *rowPins, unsigned char *colPins,
	   	unsigned char *keyMaps,
	    unsigned char rows, unsigned char cols);

char xqKbGetKey(XqKb* kb);

#endif
