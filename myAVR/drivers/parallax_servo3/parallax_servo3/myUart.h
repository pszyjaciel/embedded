
#ifndef MYUART_H_
#define MYUART_H_

unsigned char USARTReadChar(void);
void USARTWriteChar(unsigned char data);
void USART_putstring(char* StringPtr);
void USART_init(void);


#endif /* MYUART_H_ */