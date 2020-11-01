/*
* Created: 2/8/2015 5:14:52 PM
* Author: root

* zmienilem na UCSR3 (06.08.2015)
* dla F_CPU 11059200UL mnoznik jest 24, a predkosc terminala to 14400.
*/

#include <avr/io.h>

// u:\ICT\4th_semester\SEPI4\atmega2560.pdf page 230
// #define F_CPU 7372800UL		// F_CPU zdefiniowany w delay.h linia 91
#define BAUDRATE 9600			// terminal dziala na 14400
// #define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1) // dla 7372800UL: 47 (0x2f) (0b00101111)
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 24UL))) - 1)	
// mnoznik = ((F_CPU / 48)) / 9600 = 22 (okolo)

unsigned char USARTReadChar(void)
{
	// while(!(UCSR0A & (1 << RXC0)))		// Wait untill a data is available
	while(!(UCSR3A & (1 << RXC3)))		// Wait until a data is available
	{
		//Do nothing
	}
	// return UDR0;
	return UDR3;
}

//This function writes the given "data" to the USART which then transmit it via TX line
void USARTWriteChar(unsigned char data)
{
	// while(!(UCSR0A & (1<<UDRE0)))		// Wait untill the transmitter is ready
	while(!(UCSR3A & (1<<UDRE3)))		// Wait untill the transmitter is ready
	{
		//Do nothing
		;
	}
	// UDR0 = data;						// Now write the data to USART buffer
	UDR3 = data;						// Now write the data to USART buffer
}

void USART_putstring(char* StringPtr){
	
	while(*StringPtr != 0x00)
	{
		USARTWriteChar(*StringPtr);
		StringPtr++;
	}
}

void USART_init(void) {
	// UBRR0H = (uint8_t)(BAUD_PRESCALLER >> 8);
	// UBRR0L = (uint8_t)(BAUD_PRESCALLER);
	
	UBRR3H = (uint8_t)(BAUD_PRESCALLER >> 8);
	UBRR3L = (uint8_t)(BAUD_PRESCALLER);
	
	// UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	// UCSR0C = ((1 << UCSZ00) | (1 << UCSZ01));
	
	UCSR3B = (1 << RXEN3) | (1 << TXEN3);		// 
	UCSR3C = ((1 << UCSZ30) | (1 << UCSZ31));	// 8-bit
}