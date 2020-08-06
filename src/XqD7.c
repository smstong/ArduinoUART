#include "XqD7.h"
#include "XqGpio.h"

/* graph maps 
 * format: {c, 0bABCDEFGDp}
 * */
static unsigned char maps[][2] = {
	{'1', 0b01100000},
	{'2', 0b11011010},
	{'3', 0b11110010},
	{'4', 0b01100110},
	{'5', 0b10110110},
	{'6', 0b10111110},
	{'7', 0b11100000},
	{'8', 0b11111110},
	{'9', 0b11110110},
	{'0', 0b11111100},
	{'.', 0b00000001},
	{'E', 0b10011110},
};

static void write_char(unsigned char pins[8], unsigned char c)
{
	int i=0;
	unsigned char g = 0; /* graph */
	int n = sizeof(maps)/sizeof(maps[0]);
	for(i=0; i<n; i++){
		if(c == maps[i][0]){
			g = maps[i][1];
			break;
		}
	}
	for(i=0; i<8; i++){
		xqGpioWrite(pins[i], (((g<<i)&0x80)>>7) == 1 ? HIGH : LOW);
	}
}


/************************** API section ***********************/
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
		int selPins)
{
	d->segPin[0] = pinA;
	d->segPin[1] = pinB;
	d->segPin[2] = pinC;
	d->segPin[3] = pinD;
	d->segPin[4] = pinE;
	d->segPin[5] = pinF;
	d->segPin[6] = pinG;
	d->segPin[7] = pinDp;

	int i=0;
	d->selPins = selPins;
	for(i=0; i<selPins; i++){
		d->selPin[i] = selPin[i];
		xqGpioSetMode(selPin[i], OUT);
	}
	for(i=0; i<8; i++){
		xqGpioSetMode(d->segPin[i], OUT);
	}
}

void xqD7Write(XqD7 *d, int nSel, char c)
{
	if(nSel<0 || nSel >= d->selPins) {
		return;
	}
	int i=0;
	for(i=0; i<d->selPins; i++){
		if(i == nSel){
			xqGpioWrite(d->selPin[i], LOW);
		}else{
			xqGpioWrite(d->selPin[i], HIGH);
		}
	}
	write_char(d->segPin, (unsigned char)c);
}
