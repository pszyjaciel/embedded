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

// sie mi nie podoba.. - hiba jest ok
void clearDisplay() {
	for (int i = 0; i < 8; i++) {
		sendData(i << 1, 0);
		//		0 << 1: 00000000 (0)
		//		1 << 1: 00000010 (2)
		//		2 << 1: 00000100 (4)
		//		3 << 1: 00000110 (6)
		//		4 << 1: 00001000 (8)
		//		5 << 1: 00001010 (10)
		//		6 << 1: 00001100 (12)
		//		7 << 1: 00001110 (14)
	}
}

void clear1stDisplayModule() {
	for (int i = 0; i < 4; i++) {
		sendData(i << 1, 0);
	}
}

void clear2ndDisplayModule() {
	for (int i = 4; i < 8; i++) {
		sendData(i << 1, 0);
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

// 0xffff: 65535
// 0x000fffff: 1048575
// 0x00ffffff: 16777215
// 0x0fffffff: 268435455
// 0xffffffff: 4294967295

void printNumber(uint32_t myNumber) {
	if (myNumber < 10) {
		sendData(14, NUMBER_FONT[myNumber]);
		sendData(15, 0);
	} else if (myNumber > 9 && myNumber < 100) {
		//SEGGER_RTT_printf(0, "myNumber / 10: \r\n", myNumber / 10);
		//SEGGER_RTT_printf(0, "myNumber % 10: \r\n", myNumber % 10);
		sendData(12, NUMBER_FONT[myNumber / 10]);
		sendData(13, 0);
		sendData(14, NUMBER_FONT[myNumber % 10]);
		sendData(15, 0);
	} else if (myNumber > 99 && myNumber < 1000) {
		sendData(10, NUMBER_FONT[(myNumber / 100) % 10]);
		sendData(11, 0);
		sendData(12, NUMBER_FONT[(myNumber / 10) % 10]);
		sendData(13, 0);
		sendData(14, NUMBER_FONT[myNumber % 10]);
		sendData(15, 0);
	} else if (myNumber > 999 && myNumber < 10000) {
		sendData(8, NUMBER_FONT[(myNumber / 1000) % 10]);
		sendData(9, 0);
		sendData(10, NUMBER_FONT[(myNumber / 100) % 10]);
		sendData(11, 0);
		sendData(12, NUMBER_FONT[(myNumber / 10) % 10]);
		sendData(13, 0);
		sendData(14, NUMBER_FONT[myNumber % 10]);
		sendData(15, 0);
	} else if (myNumber > 9999 && myNumber < 100000) {
		sendData(6, NUMBER_FONT[(myNumber / 10000) % 10]);
		sendData(7, 0);
		sendData(8, NUMBER_FONT[(myNumber / 1000) % 10]);
		sendData(9, 0);
		sendData(10, NUMBER_FONT[(myNumber / 100) % 10]);
		sendData(11, 0);
		sendData(12, NUMBER_FONT[(myNumber / 10) % 10]);
		sendData(13, 0);
		sendData(14, NUMBER_FONT[myNumber % 10]);
		sendData(15, 0);
	} else if (myNumber > 99999 && myNumber < 1000000) {
		sendData(4, NUMBER_FONT[(myNumber / 100000) % 10]);
		sendData(5, 0);
		sendData(6, NUMBER_FONT[(myNumber / 10000) % 10]);
		sendData(7, 0);
		sendData(8, NUMBER_FONT[(myNumber / 1000) % 10]);
		sendData(9, 0);
		sendData(10, NUMBER_FONT[(myNumber / 100) % 10]);
		sendData(11, 0);
		sendData(12, NUMBER_FONT[(myNumber / 10) % 10]);
		sendData(13, 0);
		sendData(14, NUMBER_FONT[myNumber % 10]);
		sendData(15, 0);
	} else if (myNumber > 999999 && myNumber < 10000000) {
		sendData(2, NUMBER_FONT[(myNumber / 1000000) % 10]);
		sendData(3, 0);
		sendData(4, NUMBER_FONT[(myNumber / 100000) % 10]);
		sendData(5, 0);
		sendData(6, NUMBER_FONT[(myNumber / 10000) % 10]);
		sendData(7, 0);
		sendData(8, NUMBER_FONT[(myNumber / 1000) % 10]);
		sendData(9, 0);
		sendData(10, NUMBER_FONT[(myNumber / 100) % 10]);
		sendData(11, 0);
		sendData(12, NUMBER_FONT[(myNumber / 10) % 10]);
		sendData(13, 0);
		sendData(14, NUMBER_FONT[myNumber % 10]);
		sendData(15, 0);
	} else if (myNumber > 9999999 && myNumber < 100000000) {
		sendData(0, NUMBER_FONT[(myNumber / 10000000) % 10]);
		sendData(1, 0);
		sendData(2, NUMBER_FONT[(myNumber / 1000000) % 10]);
		sendData(3, 0);
		sendData(4, NUMBER_FONT[(myNumber / 100000) % 10]);
		sendData(5, 0);
		sendData(6, NUMBER_FONT[(myNumber / 10000) % 10]);
		sendData(7, 0);
		sendData(8, NUMBER_FONT[(myNumber / 1000) % 10]);
		sendData(9, 0);
		sendData(10, NUMBER_FONT[(myNumber / 100) % 10]);
		sendData(11, 0);
		sendData(12, NUMBER_FONT[(myNumber / 10) % 10]);
		sendData(13, 0);
		sendData(14, NUMBER_FONT[myNumber % 10]);
		sendData(15, 0);
	} else {
		// too big
		sendData(0, FONT_DEFAULT[34]);	// T
		sendData(1, 0);
		sendData(2, FONT_DEFAULT[79]);	// o
		sendData(3, 0);
		sendData(4, FONT_DEFAULT[79]);	// o
		sendData(5, 0);
		sendData(6, FONT_DEFAULT[0]);	// ' '
		sendData(7, 0);
		sendData(8, FONT_DEFAULT[66]);	// b
		sendData(9, 0);
		sendData(10, FONT_DEFAULT[73]);	// i
		sendData(11, 0);
		sendData(12, FONT_DEFAULT[71]);	// g
		sendData(13, 0);
	}
}

// wyswietlacz pjerszy ot prawej
void print1stNumber(uint16_t myNumber) {
	bool cleared;
	if (myNumber < 10) {
		sendData(14, NUMBER_FONT[myNumber]);
		sendData(15, 0);
	} else if (myNumber > 9 && myNumber < 100) {
		sendData(12, NUMBER_FONT[myNumber / 10]);
		sendData(13, 0);
		sendData(14, NUMBER_FONT[myNumber % 10]);
		sendData(15, 0);
	} else if (myNumber > 99 && myNumber < 1000) {
		sendData(10, NUMBER_FONT[(myNumber / 100) % 10]);
		sendData(11, 0);
		sendData(12, NUMBER_FONT[(myNumber / 10) % 10]);
		sendData(13, 0);
		sendData(14, NUMBER_FONT[myNumber % 10]);
		sendData(15, 0);
	} else if (myNumber > 999 && myNumber < 10000) {
		sendData(8, NUMBER_FONT[(myNumber / 1000) % 10]);
		sendData(9, 0);
		sendData(10, NUMBER_FONT[(myNumber / 100) % 10]);
		sendData(11, 0);
		sendData(12, NUMBER_FONT[(myNumber / 10) % 10]);
		sendData(13, 0);
		sendData(14, NUMBER_FONT[myNumber % 10]);
		sendData(15, 0);
	} else if (myNumber == 10000) {
		clear1stDisplayModule();
	} else {
		sendData(8, FONT_DEFAULT[0]);	// ' '
		sendData(9, 0);
		sendData(10, FONT_DEFAULT[37]);	// E
		sendData(11, 0);
		sendData(12, FONT_DEFAULT[82]);	// r
		sendData(13, 0);
		sendData(14, FONT_DEFAULT[82]);	// r
		sendData(15, 3);
	}
}

// pjerszy ot lewej
void print2ndNumber(uint16_t myNumber) {
	bool cleared;

	if (myNumber < 10) {
		sendData(6, NUMBER_FONT[myNumber]);
		sendData(7, 0);
	} else if (myNumber > 9 && myNumber < 100) {
		sendData(4, NUMBER_FONT[myNumber / 10]);
		sendData(5, 0);
		sendData(6, NUMBER_FONT[myNumber % 10]);
		sendData(7, 0);
	} else if (myNumber > 99 && myNumber < 1000) {
		sendData(2, NUMBER_FONT[(myNumber / 100) % 10]);
		sendData(3, 0);
		sendData(4, NUMBER_FONT[(myNumber / 10) % 10]);
		sendData(5, 0);
		sendData(6, NUMBER_FONT[myNumber % 10]);
		sendData(7, 0);
	} else if (myNumber > 999 && myNumber < 10000) {
		sendData(0, NUMBER_FONT[(myNumber / 1000) % 10]);
		sendData(1, 0);
		sendData(2, NUMBER_FONT[(myNumber / 100) % 10]);
		sendData(3, 0);
		sendData(4, NUMBER_FONT[(myNumber / 10) % 10]);
		sendData(5, 0);
		sendData(6, NUMBER_FONT[myNumber % 10]);
		sendData(7, 0);
	} else if (myNumber == 10000) {
		clear2ndDisplayModule();
	} else {
		sendData(0, FONT_DEFAULT[0]);	// ' '
		sendData(1, 0);
		sendData(2, FONT_DEFAULT[37]);	// E
		sendData(3, 0);
		sendData(4, FONT_DEFAULT[82]);	// r
		sendData(5, 0);
		sendData(6, FONT_DEFAULT[82]);	// r
		sendData(7, 3);
	}

}

