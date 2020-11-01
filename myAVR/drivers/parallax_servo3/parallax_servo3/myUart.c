/*
 * Created: 2/8/2015 5:14:52 PM
 * Author: root
 */ 

#include <avr/io.h>

#define F_CPU 7372800UL	
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

unsigned char USARTReadChar(void)
{
	while(!(UCSR0A & (1 << RXC0)))		// Wait untill a data is available
	{
		//Do nothing
	}
	return UDR0;
}

//This fuction writes the given "data" to the USART which then transmit it via TX line
void USARTWriteChar(unsigned char data)
{
	while(!(UCSR0A & (1<<UDRE0)))		// Wait untill the transmitter is ready
	{
		//Do nothing
		;
	}
	UDR0 = data;						// Now write the data to USART buffer
}

void USART_putstring(char* StringPtr){
	
	while(*StringPtr != 0x00)
	{
		USARTWriteChar(*StringPtr);
		StringPtr++;
	}
}

void USART_init(void) {
	UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);
	UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = ((1 << UCSZ00) | (1 << UCSZ01));
}