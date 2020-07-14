#ifndef XQ_UART_H
#define XQ_UART_H

void xqUartInit(unsigned int baud);
int xqUartSendByte(unsigned char c);
int xqUartSendMsg(unsigned char* msg, int len);
void xqUartSetByteRecvCb( void (*cb)(unsigned char));

#endif /* XQ_UART_H */
