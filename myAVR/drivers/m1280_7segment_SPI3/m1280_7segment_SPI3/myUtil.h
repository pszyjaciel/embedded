/*
 * myUtil.h
 *
 * Created: 2/17/2015 6:28:32 PM
 *  Author: tomek
 */ 


#ifndef MYUTIL_H_
#define MYUTIL_H_

#include <stdlib.h>

size_t strlen(const char *str);
void print_binByte(uint8_t byte);
void print_hexByte(uint8_t byte);
void print_hexAddress(uint16_t address);
void printStrInHex(char *aString);
void deb_print(char *aString, uint8_t byte);
void wait(uint8_t ileNopuf);


#endif /* MYUTIL_H_ */