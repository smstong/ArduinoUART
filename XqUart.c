#include "XqUart.h"
#include <avr/io.h>
#include <string.h>
#include <avr/interrupt.h>

#define TX_BUF_SIZE 256

static void on_rx_byte();
static void on_tx_byte();

ISR(USART_RX_vect)
{
	on_rx_byte();
}

ISR(USART_TX_vect)
{
	/* TXC flag is cleared automatically by hardware */
	on_tx_byte();
}

static unsigned char noTXC = 1;	  /* no TXC flag */

/****************** Tx Queue ***********************/
static unsigned char TxQ[TX_BUF_SIZE]; 	/* TX buf */
static unsigned int TxQ_n = 0;  	/* number of bytes to send */
static unsigned int TxQ_head = -1;		/* the inex of next byte to send */

/* append a char to queue */
static unsigned int TxQ_in(unsigned char c)
{
	if(TxQ_n == TX_BUF_SIZE) {
		return 1;
	}
	if(TxQ_head == -1){
		TxQ[0] = c;
		TxQ_head = 0;
		TxQ_n = 1;
		return 0;
	}
	int tail = TxQ_head + TxQ_n - 1;
	if(tail >= TX_BUF_SIZE){
		tail -=  TX_BUF_SIZE;
	}
	tail = tail + 1;
	if(tail >= TX_BUF_SIZE){
		tail = 0;
	}
	TxQ[tail] = c;
	TxQ_n ++;
	return 0;
}

/* take out a char from the queue */
static int TxQ_out(unsigned char* pc)
{
	if(TxQ_n==0){
		return 1;
	}
	*pc = TxQ[TxQ_head];
	TxQ[TxQ_head] = 0;

	TxQ_head ++;
	if(TxQ_head >= TX_BUF_SIZE){
		TxQ_head = 0;
	}
	TxQ_n--;
	return 0;
}
/****************** Tx queue end ***********************/

/* when a byte is received, call this callback */
static void (*uart_cb_byte_received)(unsigned char c) = NULL;


static void on_rx_byte()
{
	/* read UDR0 to clear RXC flag*/
	unsigned char c = UDR0;
	if(uart_cb_byte_received){
		uart_cb_byte_received(c);
	}

}

static void on_tx_byte()
{
	/* if queue is empty, 
	   TXC interrupt will not raise any more after this one.
	 */
	if(0==TxQ_n){
		noTXC = 1;
	   	return;
	}
	unsigned char c = 0;
	TxQ_out(&c);
	UDR0 = c;
}

static void uart_init(unsigned int baud)
{
	/* enable Tx, Rx, Tx interrupt, Rx interrupt */
	UCSR0B = (1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0)|(1<<TXCIE0);
	/* set 8bits-N-1 */
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);

	/* set baud rate */
	UBRR0 = (unsigned int)(1000000.0/baud) -1;
	sei();
}

static int uart_send_byte(unsigned char c)
{
	/* sending first byte to trigger TXC interrupt
	 * if TXC disappears due to queue empty.
	 */
	if(noTXC){
		noTXC = 0;
		UDR0 = c;
		return 0;
	}
	return TxQ_in(c);
}
/* send a msg asyncronously 
 * Return: 0-success, 1- TX queue is not empty
 */
static int uart_send_msg(unsigned char *msg, int len)
{
	/* TxQ, TxQ_n may be changed in INT, so disable INT here */

	int i = 0;
	int n = len;

	cli();
	if(TxQ_n + n > TX_BUF_SIZE) { /* TxQ doesn't have enough free spots */
		sei();
		return 1;
	}
	
	for(i=0; i<n; i++){
		uart_send_byte(msg[i]);
	}

	sei();
	return 0;
}

/*********************** API section *****************/
void xqUartSetByteRecvCb( void (*cb)(unsigned char))
{
	uart_cb_byte_received = cb;
}
int xqUartSendByte(unsigned char c)
{
	return uart_send_byte(c);
}
int xqUartSendMsg(unsigned char* msg, int len)
{
	uart_send_msg(msg, len);
}
void xqUartInit(unsigned int baud)
{
	uart_init(baud);
}
