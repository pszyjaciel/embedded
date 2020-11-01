#ifndef USSCALC_H_
#define USSCALC_H_

#include "myUart.h"

uint8_t myTelegram[14];
uint8_t previous, heartbeat;

uint16_t getValue(uint16_t myParam);
uint16_t * getAllValues(uint16_t* mmParametersArr, uint8_t length);

#endif /* USSCALC_H_ */
