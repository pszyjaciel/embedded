#include "tm1638.h"

// CLK: In writing, the data is transferred on the rising edge of the CLK.
// The least significant bits are sent first
void outputByte(uint8_t myDIO) {
	//DIGITAL_IO_SetOutputLow(&IOSTB);
	for (int i = 0; i < 8; i++) {
		set_CLK_Low;						// min 400ns clock pulse width
		(myDIO & 1) ? DIGITAL_IO_SetOutputHigh(&IODIO) : DIGITAL_IO_SetOutputLow(&IODIO);
		set_CLK_High;						// po haj jest low.
		myDIO = myDIO >> 1;					// dawaj kolejny bit
	}
	//DIGITAL_IO_SetOutputHigh(&IOSTB);
}

void sendCommand(uint8_t cmd) {
	set_STB_Low;
	outputByte(cmd);
	set_STB_High;	// A transmitted block is terminated by the STB line returning to high level.
	//SEGGER_RTT_printf(0, "cmd: %02x \r\n", cmd);
}

// address 0..15, po dwa bajty na jeden segment
void sendData(uint8_t address, uint8_t data) {
	sendCommand(0x44);		// Addressing mode: fixed address
	set_STB_Low;
	outputByte(0xC0 | address);
	// outputByte(address | 1 << 7 | 1 << 6);
	outputByte(data);
	set_STB_High;
}

void clearDisplay() {
	for (int i = 0; i < 8; i++) {
		sendData(i << 1, 0);
		//		1 << 1: 00000010
		//		2 << 1: 00000100
		//		3 << 1: 00000110
		//		4 << 1: 00001000
		//		5 << 1: 00001010
		//		6 << 1: 00001100
		//		7 << 1: 00001110

	}
}

// intensity: 0..7, active: 0..1
void setupDisplay(bool active, uint8_t intensity) {
	uint8_t myCommand = (0x80 | (active ? 8 : 0) | min(7, intensity));
	sendCommand(myCommand);
}

//Low STB
//0x40; Command for writing to incrementing auto address
//High STB
//Low STB
//0xC0; address of the first digit on the left
//0x00; all off
//repeat the data 15 more times
//High STB
void resetLEDKey() {
	sendCommand(0x40); // set auto increment mode
	set_STB_Low;
	outputByte(0xc0);   // set starting address to 0
	for (uint8_t i = 0; i < 16; i++) {
		outputByte(0x00);
	}
	set_STB_High;
}

void myInitLEDKey() {
	resetLEDKey();	// musi ma byc
	setupDisplay(true, 0);
	clearDisplay();
}

void printChar(uint8_t myChar) {
	sendData(0, FONT_DEFAULT[myChar + 0]);
	sendData(1, 0);
	sendData(2, FONT_DEFAULT[myChar + 1]);
	sendData(3, 0);
	sendData(4, FONT_DEFAULT[myChar + 2]);
	sendData(5, 0);
	sendData(6, FONT_DEFAULT[myChar + 3]);
	sendData(7, 0);
	sendData(8, FONT_DEFAULT[myChar + 4]);
	sendData(9, 0);
	sendData(10, FONT_DEFAULT[myChar + 5]);
	sendData(11, 0);
	sendData(12, FONT_DEFAULT[myChar + 6]);
	sendData(13, 0);
	sendData(14, FONT_DEFAULT[myChar + 7]);
	sendData(15, 0);


}