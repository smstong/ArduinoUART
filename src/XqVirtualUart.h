/***************************************************************
 * Vitual UART driver for Arduino
 *
 * ************************************************************/
#ifndef _XQ_VIRTUAL_UART_H
#define _XQ_VIRTUAL_UART_H

typedef unsigned char u8;
typedef unsigned int u16;

typedef struct _XqVirtualUart 
{
	u8 pinTx;
	u8 pinRx;
	u16 baud;
	/* STOP: 1 bit */
	/* PARITY: NO */
	/* DATA len: 8 bits */
}XqVirtualUart;

void xqVirtualUartInit(XqVirtualUart* s, u8 pinTx, u8 pinRx, u16 baud);
void xqVirtualUartSendByte(XqVirtualUart* s, u8 byte_out);
u8 xqVirtualUartRecvByte(XqVirtualUart* s);

#endif /* #ifdef _XQ_VIRTUAL_UART_H */
