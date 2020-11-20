
#ifndef TM1638_H_
#define TM1638_H_

#include <DAVE.h>
#include "TM16XXFonts.h"

uint32_t event_count;

#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define set_STB_High			DIGITAL_IO_SetOutputHigh(&IOSTB)
#define set_STB_Low				DIGITAL_IO_SetOutputLow(&IOSTB)
#define set_CLK_High			DIGITAL_IO_SetOutputHigh(&IOCLK)
#define set_CLK_Low				DIGITAL_IO_SetOutputLow(&IOCLK)

void sendCommand(uint8_t cmd);
void sendData(uint8_t address, uint8_t data);

void clearDisplay();
void myInitLEDKey();
void printChar(uint8_t myChar);


#endif /* TM1638_H_ */
