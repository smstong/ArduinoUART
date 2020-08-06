/***************************************************************
 * I2C driver for Arduino
 *
 *
 * ************************************************************/
#ifndef _XQ_I2C_H
#define _XQ_I2C_H

void xqI2cInit(void);

/* return -1 for error */
int xqI2cStart(void);

/* return -1 for error */
int xqI2cReadByte(unsigned char ifAck);

/* return -1 for error */
int xqI2cWriteByte(unsigned char byte_out);

void xqI2cStop(void);

#endif /* #ifdef _XQ_I2C_H */
