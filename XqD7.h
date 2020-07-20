/***************************************************************
 * Digital 7 segment display driver
 * (Common-cathode)
 *
 * ************************************************************/
#ifndef XQ_D7_H
#define XQ_D7_H

#define XQ_D7_MAX 16

typedef struct XqD7
{
	unsigned char segPin[8];		/* segment pins */
	unsigned char selPin[XQ_D7_MAX];/* select pins */
	int selPins;	/* number of digit pins */
}XqD7;

void xqD7Init(XqD7* d, 
		unsigned char pinA,
		unsigned char pinB,
		unsigned char pinC,
		unsigned char pinD,
		unsigned char pinE,
		unsigned char pinF,
		unsigned char pinG,
		unsigned char pinDp,
		unsigned char selPin[],
		int selPins);

/* write c('1','2',...) on nSel(0,1,..) digit */
void xqD7Write(XqD7* d, int nSel, char c);

#endif
