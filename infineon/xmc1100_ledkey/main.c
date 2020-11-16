// http://www.microcontroller.it/Tutorials/Elettronica/componenti/tm1638.htm
// https://github.com/rjbatista/tm1638-library/blob/master/TM16XX.cpp
// https://github.com/MartyMacGyver/TM1638-demos-and-examples/blob/master/README.md

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "MyUtils.h"

uint32_t event_count;
volatile bool czasMinou;

#define min(a,b)            (((a) < (b)) ? (a) : (b))

void outputByValue2(uint8_t myValue) {
	switch (myValue) {
	case 0:
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_3);
		break;
	case 1:
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_3);
		break;
	case 2:
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_3);
		break;
	case 3:
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_3);
		break;

	case 4:
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_3);
		break;

	case 5:
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_3);
		break;

	case 6:
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_3);
		break;

	case 7:
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_3);
		break;

	case 8:
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_3);
		break;

	case 9:
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_3);
		break;

	case 10:
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_3);
		break;

	case 11:
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_3);
		break;

	case 12:
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_3);
		break;

	case 13:
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_3);
		break;

	case 14:
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_3);
		break;

	case 15:
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputHigh(&DIGITAL_IO_3);
		break;

	default:
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_0);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_1);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_2);
		DIGITAL_IO_SetOutputLow(&DIGITAL_IO_3);
		break;
	}
}

void Time_Interval_Event(void) {
	//TrackSignalByValue(0);
	czasMinou = true;
	/* Acknowledge Period Match interrupt generated on TIMER_CCU_1 */
	TIMER_ClearEvent(&TIMER_0);
	TIMER_Stop(&TIMER_0);
}

void myDelayMS(uint32_t milliSec) {
	czasMinou = false;
	TIMER_SetTimeInterval(&TIMER_0, milliSec * 100000);
	TIMER_Start(&TIMER_0);
	//TrackSignalByValue(2);
	while (!czasMinou) {
		;
	}
}

// sie udalo uzyskac 5microsec
void myDelayUS(uint32_t microSec) {
	if (microSec < 100) {
		microSec = 100;		// musi ma byc
	}
	czasMinou = false;
	TIMER_SetTimeInterval(&TIMER_0, microSec * 10);
	//TIMER_SetTimeInterval(&TIMER_0, microSec);

	TIMER_Start(&TIMER_0);
	//TrackSignalByValue(1);
	while (!czasMinou) {
		;
	}
}

//SEGGER_RTT_printf(0, "%08x\r\n", (myDIO >> i) & 0xfe);
//SEGGER_RTT_printf(0, "%d, %08x\r\n", i, (myDIO >> i) & 0x01);

// The least significant bits are sent first
void mySend(uint8_t myDIO) {
	for (int i = 0; i < 8; i++) {

		//DIGITAL_IO_SetOutputLow(&IOCLK);	// min 400ns clock pulse width
		if (myDIO & 1) {
			DIGITAL_IO_SetOutputHigh(&IODIO);
			//TrackSignalByValue(2);
		} else {
			DIGITAL_IO_SetOutputLow(&IODIO);
			//TrackSignalByValue(1);
		}
		//(myDIO & 1) ? DIGITAL_IO_SetOutputHigh(&IODIO) : DIGITAL_IO_SetOutputLow(&IODIO);
		myDIO = myDIO >> 1;
		TrackSignalByValue(2);
		DIGITAL_IO_SetOutputHigh(&IOCLK);
		//TrackSignalByValue(4);
		myDelayUS(1);
		DIGITAL_IO_SetOutputLow(&IOCLK);	// min 400ns clock pulse width
		TrackSignalByValue(1);
		myDelayUS(1);
	}
}

void sendCommand(uint8_t cmd) {
	TrackSignalByValue(1);
	DIGITAL_IO_SetOutputLow(&IOSTB);
	mySend(cmd);
	DIGITAL_IO_SetOutputHigh(&IOSTB);
	TrackSignalByValue(0);
}

void sendData(uint8_t address, uint8_t data) {
	sendCommand(0x44);
	DIGITAL_IO_SetOutputLow(&IOSTB);
	mySend(0xC0 | address);
	mySend(data);
	DIGITAL_IO_SetOutputHigh(&IOSTB);
}

void clearDisplay() {
	for (int i = 0; i < 8; i++) {
		sendData(i << 1, 0);
	}
}

void setupDisplay(bool active, uint8_t intensity) {
	sendCommand(0x80 | (active ? 8 : 0) | min(7, intensity));
}

void setDisplay(const uint8_t values[], unsigned int length) {
	for (int i = 0; i < 8; i++) {
		int val = 0;

		for (int j = 0; j < length; j++) {
			val |= ((values[j] >> i) & 1) << (1 - j - 1);
		}
		sendData(i << 1, val);
	}
}

//void setupDisplay(bool active, uint8_t intensity)
//{
//  sendCommand(0x80 | (active ? 8 : 0) | min(7, intensity));
//
//  // necessary for the TM1640
//	DIGITAL_IO_SetOutputLow(&IOSTB);
//	DIGITAL_IO_SetOutputLow(&IOCLK);
//	DIGITAL_IO_SetOutputHigh(&IOCLK);
//	DIGITAL_IO_SetOutputHigh(&IOSTB);
//}

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
	DIGITAL_IO_SetOutputLow(&IOSTB);
	mySend(0xc0);   // set starting address to 0
	for (uint8_t i = 0; i < 16; i++) {
		mySend(0x00);
	}
	DIGITAL_IO_SetOutputHigh(&IOSTB);
}

void myInitLEDKey() {
	DIGITAL_IO_SetOutputLow(&IOSTB);
	//myDelayUS(10);
	mySend(0x40);
	mySend(0x8f);
	DIGITAL_IO_SetOutputHigh(&IOSTB);
	//myDelayUS(10);

	resetLEDKey();
	setupDisplay(true, 127);

}

void sendChar(uint8_t pos, uint8_t data, bool dot) {
	sendData(pos << 1, data | (dot ? 0b10000000 : 0));
}

void setDisplayDigit(uint8_t digit, uint8_t pos, bool dot, const uint8_t numberFont[]) {
	sendChar(pos, numberFont[digit & 0xF], dot);
}

// https://blog.3d-logic.com/2015/01/10/using-a-tm1638-based-board-with-arduino/
int main(void) {
	DAVE_STATUS_t status;
	status = DAVE_Init(); /* Initialization of DAVE APPs  */

	if (status != DAVE_STATUS_SUCCESS) {
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");

		while (1U) {
		}
	}

	SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);
	DIGITAL_IO_SetOutputHigh(&IOCLK);
	DIGITAL_IO_SetOutputHigh(&IOSTB);
	myInitLEDKey();

	while (1U) {
		myDelayUS(1000);
		DIGITAL_IO_ToggleOutput(&LED0);

//		DIGITAL_IO_SetOutputLow(&IOSTB);
//		mySend(0x40);	// Write command with incrementing auto address
//		DIGITAL_IO_SetOutputHigh(&IOSTB);
//		myDelayUS(1000);

//		DIGITAL_IO_SetOutputLow(&IOSTB);
//		mySend(0xc0);	// address of the first digit on the left
//		mySend(0x06);	// 00000110 digit 1 segments b,c on
//		mySend(0x01);	// Red LED
//		mySend(0xdb);	// 11011011 digit 2 segments a,b,d,g,dp on
//		mySend(0x02);	// Green LED
//		mySend(0xcf);	// 11001111 digit 3 segments a,b,c,d,e,g on
//		mySend(0x01);	// Red LED
//		mySend(0xb6);	// 10110110 digit 4 segments b,c,e,f,dp accesses i
//		mySend(0x02);	// Green LED
//		DIGITAL_IO_SetOutputHigh(&IOSTB);

		// to dziala!
		//sendCommand(0x44);  // set single address
		sendData(0, 0x06);
		sendData(1, 0xdb);
		sendData(2, 0xcf);
		sendData(3, 0xb6);
		sendData(4, 0x06);
		sendData(5, 0xdb);
		sendData(6, 0xcf);
		sendData(7, 0xb6);
		sendData(8, 0x06);
		sendData(9, 0xdb);
		sendData(10, 0xcf);
		sendData(11, 0xb6);
		sendData(12, 0x06);
		sendData(13, 0xdb);
		sendData(14, 0xcf);
		sendData(15, 0xb6);


//		DIGITAL_IO_SetOutputLow(&IOSTB);
//		mySend(0xc0); // 1st digit
//		mySend(0xff);
//		DIGITAL_IO_SetOutputHigh(&IOSTB);
//
//		DIGITAL_IO_SetOutputLow(&IOSTB);
//		mySend(0xc5);
//		mySend(0x01);
//		DIGITAL_IO_SetOutputHigh(&IOSTB);
//
//		DIGITAL_IO_SetOutputLow(&IOSTB);
//		mySend(0xcb);
//		mySend(0x01);
//		DIGITAL_IO_SetOutputHigh(&IOSTB);
//
//		DIGITAL_IO_SetOutputLow(&IOSTB);
//		mySend(0xce);
//		mySend(0xff);
//		DIGITAL_IO_SetOutputHigh(&IOSTB);

		// test dividera
//		for (int i = 0; i < 4; i++) {
//			TrackSignalByValue(i);
//			myDelayMS(1);
//		}
//		myDelayMS(10);
	}

}

//	DIGITAL_IO_SetOutputLow(&IOSTB);
//	myDelayUS(10);
//	mySend(0xc0);
//	for (int i = 0; i < 16; i++) {
//		mySend(0x00);
//	}
//	DIGITAL_IO_SetOutputHigh(&IOSTB);
//	myDelayUS(10);
//
//	DIGITAL_IO_SetOutputLow(&IOSTB);
//	myDelayUS(10);
//	mySend(0x44);
//	DIGITAL_IO_SetOutputHigh(&IOSTB);
//	myDelayUS(10);
//
//	DIGITAL_IO_SetOutputLow(&IOSTB);
//	myDelayUS(10);
//	mySend(0xc0);
//	mySend(0x06);
//	DIGITAL_IO_SetOutputHigh(&IOSTB);
//	myDelayUS(10);
//
//	DIGITAL_IO_SetOutputLow(&IOSTB);
//	myDelayUS(10);
//	mySend(0xce);
//	mySend(0x7f);
//	DIGITAL_IO_SetOutputHigh(&IOSTB);
//	myDelayUS(10);
//
//	DIGITAL_IO_SetOutputLow(&IOSTB);
//	DIGITAL_IO_SetOutputLow(&IOCLK);
//	myDelayUS(10);
//	DIGITAL_IO_SetOutputHigh(&IOCLK);
//	DIGITAL_IO_SetOutputHigh(&IOSTB);
