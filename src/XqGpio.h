/***************************************************************
 * GPIO driver for Arduino
 *
 * Only Digital Read/Write now..
 *  
 * ************************************************************/
#ifndef XQ_GPIO_H
#define XQ_GPIO_H

#define IN 1
#define OUT 0

#define HIGH 1
#define LOW 0

#define A0 14
#define A1 15
#define A2 16
#define A3 17
#define A4 18
#define A5 19

/* pin: 0-13, A0-A5; mode: IN/OUT */
void xqGpioSetMode(unsigned char pin, unsigned char mode);

/* pin: 0-13, A0-A5; level: HIGH/LOW */
void xqGpioWrite(unsigned char pin, unsigned char level);

unsigned char xqGpioRead(unsigned char pin);

#endif
