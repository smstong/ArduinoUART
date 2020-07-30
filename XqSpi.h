/***************************************************************
 * SPI driver for Arduino
 *
 * Note: single-byte only now.
 *
 * (1)hardware connection (Arduino as a master)
 * Arduino pin     SPI Master    	 other SPI slave devices
 * 		13			SPI_CLK      <---> SPI_CLK(s)
 * 		12			SPI_MISO	 <---> SPI_MISO(s)
 * 		11			SPI_MOSI	 <---> SPI_MOSI(s)
 *
 * 		10			SPI_SS		 <---> SPI_SS(device 1)
 * 		any			SPI_SS		 <---> SPI_SS(device 2)
 * 		any			SPI_SS		 <---> SPI_SS(device n)
 *
 * (2)hardware connection (Arduino as a slave)
 * Arduino pin     SPI Slave     	 other SPI master
 * 		13			SPI_CLK      <---> SPI_CLK
 * 		12			SPI_MISO	 <---> SPI_MISO
 * 		11			SPI_MOSI	 <---> SPI_MOSI
 * 		10			SPI_SS		 <---> Master's any OUTPUT port(SS included)
 * ************************************************************/
#ifndef _XQ_SPI_H
#define _XQ_SPI_H


#define XQ_SPI_MODE_MASTER 	1
#define XQ_SPI_MODE_SLAVE 	2

void xqSpiInit(char mode);
void xqSpiAddSlave(unsigned char pinSS);

/* as a master */
void xqSpiEnableSlave(unsigned char pinSS);
void xqSpiDisableSlave(unsigned char pinSS);
void xqSpiSendByte(unsigned char c);

/* as a slave */
unsigned char xqSpiRecvByte();

#endif /* #ifndef _XQ_SPI_H */
