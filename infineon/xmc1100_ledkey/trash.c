/*
 * trash.c
 *
 *  Created on: Nov 20, 2020
 *      Author: arleta
 */
//SEGGER_RTT_printf(0, "%08x\r\n", (myDIO >> i) & 0xfe);
//SEGGER_RTT_printf(0, "%d, %08x\r\n", i, (myDIO >> i) & 0x01);


// to dziala!
//sendCommand(0x44);  // set single address
//		sendData(0, 0x06);
//		sendData(1, 0xdb);
//		sendData(2, 0xcf);
//		sendData(3, 0xb6);
//		sendData(4, 0x06);
//		sendData(5, 0xdb);
//		sendData(6, 0xcf);
//		sendData(7, 0xb6);
//		sendData(8, 0x06);
//		sendData(9, 0xdb);
//		sendData(10, 0xcf);
//		sendData(11, 0xb6);
//		sendData(12, 0x06);
//		sendData(13, 0xdb);
//		sendData(14, 0xcf);
//		sendData(15, 0xb6);

//	DIGITAL_IO_SetOutputHigh(&IOCLK);
//	DIGITAL_IO_SetOutputHigh(&IOSTB);

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

//	DIGITAL_IO_SetOutputLow(&IOSTB);
//	mySend(0x40);
//	mySend(0x8f);
//	DIGITAL_IO_SetOutputHigh(&IOSTB);

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

//void sendChar(uint8_t pos, uint8_t data, bool dot) {
//	sendData(pos << 1, data | (dot ? 0b10000000 : 0));
//}
//
//void setDisplayDigit(uint8_t digit, uint8_t pos, bool dot, const uint8_t numberFont[]) {
//	sendChar(pos, numberFont[digit & 0xF], dot);
//}

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

//void setDisplay(const uint8_t values[], unsigned int length) {
//	for (int i = 0; i < 8; i++) {
//		int val = 0;
//
//		for (int j = 0; j < length; j++) {
//			val |= ((values[j] >> i) & 1) << (1 - j - 1);
//		}
//		sendData(i << 1, val);
//	}
//}

//void clearDisplay() {
//	for (int i = 0; i < 16; i++) {
//		sendData(i, (0x00));
//	}
//}



