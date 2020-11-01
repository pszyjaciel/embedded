// u:\!Desktop\ethernut\avrstudio\myLED\myLED.atsln


#include <avr/io.h>
#include <stdlib.h>
#include "myUart.h"

// http://stackoverflow.com/questions/1733281/strlen-implementation-in-gcc
size_t strlen(const char *str)
{
	const char *s;
	for (s = str; *s; ++s)
	;
	return (s - str);
}


void print_binByte(uint8_t myByte) {
	uint8_t i;

	for (i = 0; i < 8; i++) {
		
		uint8_t result;

		result = (myByte << i) & 0x80;
		if (result == 0) {
			USARTWriteChar('0');
		}
		else {
			USARTWriteChar('1');
		}
	}
	USART_putstring("\r\n");
}


void print_hexByte(uint8_t byte) {
	char bufor[10];
	itoa(byte, bufor, 16);		// lepiej zastapic moim kodem
	
	if(bufor[1] == 0) {
		bufor[2] = 0x00;
		bufor[1] = bufor[0];
		bufor[0] = 0x30;		// wstaw 0 na poczatek buforu
	}
	
	USART_putstring(bufor);
	USART_putstring("\r\n");
}


void print_hexAddress(uint16_t address) {
	char bufor[8];
	uint8_t nibble;
	uint8_t highByte;
	uint8_t lowByte;
	
	highByte = (address & 0xFF00);
	highByte = (address >> 8);
	lowByte = (address & 0x00FF);
	
	
	nibble = (highByte & 0xF0);
	nibble = nibble >> 4;
	if (nibble > 9)	{
		nibble += 0x37;
	}
	else {
		nibble += 0x30;
	}
	bufor[0] = nibble;
	

	nibble = (highByte & 0x0F);
	if (nibble > 9)	{
		nibble += 0x37;
	}
	else {
		nibble += 0x30;
	}
	bufor[1] = nibble;
	
	
	nibble = (lowByte & 0xF0);
	nibble = (nibble >> 4);
	if (nibble > 9)	{
		nibble += 0x37;
	}
	else {
		nibble += 0x30;
	}
	bufor[2] = nibble;
	
	
	nibble = (lowByte & 0x0F);
	if (nibble > 9)	{
		nibble += 0x37;
	}
	else {
		nibble += 0x30;
	}
	bufor[3] = nibble;
	bufor[4] = 0x3A;		// dwukropek
	
	bufor[5] = 0x00;		// koniec stringa
	
	USART_putstring(bufor);
	// USART_putstring("\r\n");
}


void printStrInHex(char *aString) {
	uint8_t strLength = strlen(aString);
	
	uint8_t i;
	for(i = 0; i < strLength; i++) {
		print_hexByte(aString[i]);
	}
}

// 1. par. < 127 znakow, 2. par. to cyfra 1bajtowa
void deb_print(char *aString, uint8_t byte) {

	uint8_t strLength = strlen(aString);
	if(strLength > 127) {
		strLength = 127;
	}
	
	uint8_t bufLength = 10;
	char bufor[bufLength];
	itoa(byte, bufor, 16);
	
	if(bufor[1] == 0) {
		bufor[2] = 0x00;
		bufor[1] = bufor[0];
		bufor[0] = 0x30;		// wstaw 0 na poczatek buforu
	}
	
	uint8_t newBufLength = strLength + bufLength + 2;
	char newBuf[newBufLength];

	uint8_t i;
	for(i = 0; i < strLength; i++) {
		newBuf[i] = aString[i];
	}

	newBuf[i + 0] = ' ';
	newBuf[i + 1] = bufor[0];
	newBuf[i + 2] = bufor[1];
	newBuf[i + 3] = 0x0a;
	newBuf[i + 4] = 0x0d;
	newBuf[i + 5] = 0x00;

	// printStrInHex(newBuf);
	USART_putstring(newBuf);

}

void wait(uint8_t ileNopuf) {
	uint8_t i;
	for (i = 0; i < ileNopuf; i++)
	{
		asm("nop");
	}
	
}
