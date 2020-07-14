#include "XqUart.h"
#define F_CPU 16000000UL
#include <util/delay.h>
#include <string.h>

void OnByteRecv( unsigned char c)
{
	xqUartSendMsg(&c, 1);
}

int main()
{
	char * msg = "hello world\r\n";
	xqUartSetByteRecvCb(OnByteRecv);
	xqUartInit(9600);

	while(1){
		if(0 != xqUartSendMsg(msg, strlen(msg))){
			/* TX queue is not empty, try again later */
		}
	}
	return 0;
}

