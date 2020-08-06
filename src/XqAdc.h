/***************************************************************
 * Interrupt based ADC driver for Arduino
 *
 *
 * ************************************************************/
#ifndef XQ_ADC_H
#define XQ_ADC_H

typedef void (*XqAdcCb)(unsigned int r);

void xqAdcInit();

/***************************************************************
 * pin: A0,...,A5
   vref: 0-AREF pin, 1-AVcc, 3-internal 1.1
***************************************************************/
void xqAdcAdd(unsigned char pin, unsigned char vref, XqAdcCb cb);

void xqAdcStart();

#endif
