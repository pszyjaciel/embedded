// u:\!Desktop\ethernut\avrstudio\myLED\myLED.atsln

#include "myUtil.h"

char * short2String(short int n)
{
	static char myStr[7];
	unsigned char d4, d3, d2, d1, d0, q;
	int i;

	if (n < 0)
	{
		myStr[0] = '-';
		n = -n;
	}
	else
	{
		myStr[0] = '+';
	}
	d1 = (n >> 4) & 0x0F;
	d2 = (n >> 8) & 0x0F;
	d3 = (n >> 12) & 0x0F;

	d0 = 6 * (d3 + d2 + d1) + (n & 0x0F);
	q = (d0 * 0xCD) >> 11;
	d0 = d0 - 10 * q;

	d1 = q + 9 * d3 + 5 * d2 + d1;
	q = (d1 * 0xCD) >> 11;
	d1 = d1 - 10 * q;

	d2 = q + 2 * d2;
	q = (d2 * 0x1A) >> 8;
	d2 = d2 - 10 * q;

	d3 = q + 4 * d3;
	d4 = (d3 * 0x1A) >> 8;
	d3 = d3 - 10 * d4;
	myStr[1] = d4 + '0';
	myStr[2] = d3 + '0';
	myStr[3] = d2 + '0';
	myStr[4] = d1 + '0';
	myStr[5] = d0 + '0';
	i = 5;
	// === remove the left zero =========
	while (myStr[1] == '0' && i > 1)
	{
		int j;
		for (j = 1; j < i; j++)
		{
			myStr[j] = myStr[j + 1];
		}
		i--;
	}
	myStr[i + 1] = '\0';
	return myStr;
}


unsigned short char2short(unsigned char *val)
{
	unsigned short temp;
	unsigned short myTemp;

	myTemp = (*(val + 0));
	if (myTemp > 0x40)
		myTemp -= 0x37;          // convert chars a-f
	else
		myTemp -= 0x30;          // convert chars 0-9
	temp = myTemp * 0x1000;

	myTemp = (*(val + 1));
	if (*(val + 1) > 0x40)
		myTemp -= 0x37;          // convert chars a-f
	else
		myTemp -= 0x30;          // convert chars 0-9
	myTemp = myTemp * 0x0100;
	temp = temp + myTemp;

	myTemp = (*(val + 2));
	if (*(val + 2) > 0x40)
		myTemp -= 0x37;          // convert chars a-f
	else
		myTemp -= 0x30;          // convert chars 0-9
	myTemp = myTemp * 0x0010;
	temp = temp + myTemp;

	myTemp = (*(val + 3));
	if (*(val + 3) > 0x40)
		myTemp -= 0x37;          // convert chars a-f
	else
		myTemp -= 0x30;          // convert chars 0-9
	temp = temp + myTemp;

	return temp;
}


// http://stackoverflow.com/questions/1733281/strlen-implementation-in-gcc
static size_t strlen(const char *str)
{
	const char *s;
	for (s = str; *s; ++s)
	;
	return (s - str);
}


/**
 * @brief This function adds a suffix of two characters on the end of a string 'buffer'.
 *  In addition it adds also a space sign. Finally it terminates the string with 0.
 *  The space is used for overwrite a left eventual unused charackter in the LCD.
 * @param char * buffer, char ch1, char ch2 is a pointer to the string buffer
 * @param char ch1 is the first character added as a suffix
 * @param char ch2 is the second character added as a suffix
 * @return myBuffer as a string array
 */
char * addSuffix(char * buffer, char ch1, char ch2) {
	static char myBuffer[10];
	int x, rs;

	x = 0;
	while ((rs = buffer[x]) != 0) {
		myBuffer[x] = buffer[x];
		x++;
	}
	myBuffer[x] = ch1;
	x++;
	myBuffer[x] = ch2;
	x++;
	myBuffer[x] = ' ';
	x++;
	myBuffer[x] = 0;			// dodaje 0 na koniec stringa

	return myBuffer;
}


void print_binByte(uint8_t myByte) {
	uint8_t i;

	for (i = 0; i < 8; i++) {
		
		uint8_t result;

		result = (myByte << i) & 0x80;
		if (result == 0) {
			RS232_WriteChar('0');
		}
		else {
			RS232_WriteChar('1');
		}
	}
	RS232_putstring("\r\n");
}


void print_hexByte(uint8_t myByte) {
	char bufor[10];
	itoa(myByte, bufor, 16);		// lepiej zastapic moim kodem
	
	if(bufor[1] == 0) {
		bufor[2] = 0x00;
		bufor[1] = bufor[0];
		bufor[0] = 0x30;		// wstaw 0 na poczatek buforu
	}
	
	RS232_putstring(bufor);
	// RS232_putstring("\r\n");
}

void print_hexWord(uint16_t hword) {
	char bufor[8];
	uint8_t nibble;
	uint8_t highByte;
	uint8_t lowByte;

	highByte = (hword & 0xFF00);
	highByte = (hword >> 8);
	lowByte = (hword & 0x00FF);


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
	bufor[4] = 0x00;

	bufor[5] = 0x00;		// koniec stringa

	RS232_putstring(bufor);
	// USART_putstring("\r\n");
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
	
	RS232_putstring(bufor);
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
	RS232_putstring(newBuf);

}

//void wait(uint8_t ileNopuf) {
//	uint8_t i;
//	for (i = 0; i < ileNopuf; i++)
//	{
//		asm("nop");
//	}
//
//}
