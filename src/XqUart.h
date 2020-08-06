/***************************************************************
 * UART Driver for Ardudino
 *
 * Hardware connection:
 *
 * external    Arduino
 * Rx	<---->	Tx(pin 1)
 * Tx	<---->	Rx(pin 0)
 * GND	<---->	GND
 *
 * ************************************************************/
#ifndef XQ_UART_H
#define XQ_UART_H

void xqUartInit(unsigned int baud);
int xqUartSendByte(unsigned char c);
int xqUartSendMsg(unsigned char* msg, int len);
int xqUartSendStr(const char* str);
void xqUartSetByteRecvCb( void (*cb)(unsigned char));

#endif /* XQ_UART_H */
