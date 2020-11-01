// JP2 pin2 (T2OUT) podlaczony do pin3 portu COM w komputerze (poprzed FTDI)
// stad konfiguracja dla USART1 (a nie USART0)

#include "myUart.h"

unsigned char RS232_ReadChar(void) {
	while (!(UCSR0A & (1 << RXC0)))          // Wait until a data is available
	{
		asm volatile("nop");
	}
	return UDR0;
}

// function must be rewriten, because it blocks
unsigned char RS485_ReadChar(void)
{
	while ((UCSR1A & (1 << RXC1)) == 0) {
		asm volatile("nop");
	}
	return UDR1;									// returns 1 character
}

// This function writes a character to the USART, which then transmit it via TX line
void RS232_WriteChar(unsigned char data) {
	while ((UCSR0A & (1 << UDRE0)) == 0)          // Wait untill the transmitter is ready
	{
		asm volatile("nop");
	}
	UDR0 = data;        					  // Now write the data to USART buffer
}


void RS485_WriteChar(unsigned char data) {
	// The transmit buffer can only be written when the UDRE1 flag in the UCSRA1 Register is set.
	while ((UCSR1A & (1 << UDRE1)) == 0)
	{
		asm volatile("nop");						// wait until the UDRE1 flag is set
	}
	UDR1 = data;									// sends 1 character
}

void displayTelegram(char *message, uint8_t* myTelegram) {
	uint8_t i;

	// display telegram
	RS232_putstring("\r\n");
	RS232_putstring(message);
	for (i = 0; i < 14; i++) {
		print_hexByte(myTelegram[i]);
		RS232_putstring(" ");
	}
	RS232_putstring("\r\n");
}


// returns the MM-telegram as 8bit-array
uint8_t * RS485_QueryTelegram(uint8_t* myTelegram) {
	static uint8_t myArray[16];
	uint8_t i;

	// first we send a prepared telegram to the MM
	for (i = 0; i < 14; i++) {
		RS485_WriteChar(myTelegram[i]);						// takes 15ms to send the whole telegram
	}

	// the USART1_RX_vect receives the response from MM
	while (USART1_RX_complete == 0) {
		asm volatile("nop");								// wait until complite
		asm volatile("nop");								// 3x nop, otherwise error
		asm volatile("nop");
	}
	USART1_RX_complete = 0;									// delete the complete-flag

	for (i = 0; i < 14; i++) {
		myArray[i] = myRxArray[i];							// copy the table
	}
	return myArray;
}

void RS232_putstring(char* StringPtr) {
	while (*StringPtr != 0x00) {
		RS232_WriteChar(*StringPtr);
		StringPtr++;
	}
}

void RS485_putstring(char* StringPtr) {
	while (*StringPtr != 0x00) {
		RS485_WriteChar(*StringPtr);
		StringPtr++;
	}
}

//USART0
void RS232_init(uint32_t baudrate) {
	uint8_t prescaller = ((F_CPU / (baudrate * 16UL))) - 1;
	UBRR0H = (uint8_t) (prescaller >> 8);
	UBRR0L = (uint8_t) (prescaller);

	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
}

// USART1
// RS485 parity for the MM is always EVEN!!!
void RS485_init(uint32_t baudrate) {
	uint8_t prescaller = ((F_CPU / (baudrate * 16UL))) - 1;
	UBRR1H = (uint8_t) (prescaller >> 8);
	UBRR1L = (uint8_t) (prescaller);

	// https://www.newbiehack.com/USARTDetailed.aspx
	UCSR1B |= (1 << RXEN1) | (1 << TXEN1);				// Enable receiver and transmitter
	UCSR1B |= (1 << RXCIE1); 							// Receive Complete Interrupt Enable // | (1 << TXCIE1) ;
	UCSR1C |= (1 << UCSZ10) | (1 << UCSZ11);      	    // Table 80. UCSZn Bits Settings (page 191)
	UCSR1C |= (1 << UPM11);
	UCSR1C &= ~(1 << UPM10);          					// even parity enabled
	UCSR1C &= ~(1 << USBS0); 							// Sets 1 stop bit
	UCSR1C &= ~(1 << UMSEL1);	 						// asynchronous mode off
}

