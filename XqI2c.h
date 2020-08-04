/***************************************************************
 * I2C driver for Arduino
 *
 *
 * ************************************************************/
#ifndef _XQ_I2C_H
#define _XQ_I2C_H

void xqI2cInit(void);
void xqI2cStart(void);
unsigned char xqI2cReadByte(unsigned char ifAck);
void xqI2cWriteByte(unsigned char byte_out);
void xqI2cStop(void);

#endif /* #ifdef _XQ_I2C_H */
