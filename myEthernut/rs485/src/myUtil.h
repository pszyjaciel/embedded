#ifndef MYUTIL_H_
#define MYUTIL_H_

#include <avr/io.h>
#include <stdlib.h>

char * short2String(short int n);
unsigned short char2short(unsigned char *val);
extern void print_binByte(uint8_t myByte);
void print_hexByte(uint8_t myByte);
void print_hexWord(uint16_t word);
void print_hexAddress(uint16_t address);
void printStrInHex(char *aString);
void deb_print(char *aString, uint8_t byte);
void wait(uint8_t ileNopuf);

#endif /* MYUTIL_H_ */

// typedef unsigned int uint8_t __attribute__((__mode__(__QI__)));
