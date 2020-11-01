#ifndef USSCALC_H_
#define USSCALC_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usssend.h"

typedef unsigned char uint8_t;        // 1 byte
typedef unsigned short uint16_t;        // 2 bytes
typedef unsigned int uint32_t;        // 4 bytes

uint8_t myTelegram[14];

uint16_t getValue(uint16_t myParam);
uint16_t* getAllValues(uint16_t* myParamArr, uint8_t length);

#endif /* USSCALC_H_ */
