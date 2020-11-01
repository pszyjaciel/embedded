#ifndef MYUART_H_
#define MYUART_H_

#include "myUtil.h"

#define F_CPU 14745600UL
#define BAUDRATE 115200
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

uint8_t USART1_RX_complete;
uint8_t USART1_RX_timeout;
uint8_t myRxArray[255];

void RS232_init(uint32_t baudrate);          //USART0
void RS485_init(uint32_t baudrate);          //USART1

unsigned char RS232_ReadChar(void);
unsigned char RS485_ReadChar(void);

uint8_t * RS485_QueryTelegram(uint8_t * myTelegram);
void RS232_WriteChar(unsigned char data);
void RS485_WriteChar(unsigned char data);

void RS232_putstring(char* StringPtr);
void RS485_putstring(char* StringPtr);

#endif /* MYUART_H_ */
