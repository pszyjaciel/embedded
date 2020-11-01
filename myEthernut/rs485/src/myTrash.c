/*
 * myTrash.c
 *
 *  Created on: 02/11/2015
 *      Author: root
 */

// Tools -> External tools:
// c:\Program Files\Atmel\avrdude\avrdude.exe
// -p m128 -c usbasp -U flash:w:"$(ProjectDir)Debug\$(ItemFileName).hex":i

// U:\lua\myAVRLed2
// http://www.ethernut.de/en/hardware/enut1/index.html
// http://www.ethernut.de/en/tools/eclipse/confdebug.html
// http://www.ethernut.de/en/tools/eclipse/confeditor.html

// http://mcuoneclipse.com/2012/06/25/5-best-eclipse-plugins-1-eclox-with-doxygen-graphviz-and-mscgen/

// when start to work: fetch changes, rebase
// when done with work: commit change, push

// XMEM_init();
// testMemory();
// readRTLMemory();

// RS232_putstring("Test of RTL8019AS: ");
// TestRealtek();

// CS 	OE 		WE 		I/O 	Mode 		Power
// H 	X1) 	X1) 	High-Z 	Deselected 	Standby
// L 	H 		H 		High-Z 	Output 		Disabled Active
// L 	L 		H 		Dout 	Read 		Active
// L 	X1) 	L 		Din 	Write 		Active



//	u_short sram;
//		sram = TestExternalRam(RAMEND + 1, 0x7FFF);		// returns par2 - par1 (7fff - 1100)
//
//		if (sram != 0) {
//			print_hexAddress(sram);
//		} else {
//			RS232_putstring("some error.. \r\n");
//		}

//		status = PORTE & 0b00000010;
//		if (status == 0) {
//			PORTE = PORTE | 0b00000010;		// PORTE |= _BV(1);
//		}
//		else if (status == 1) {
//			PORTE = PORTE & 0b11111101;		// PORTE &= ~_BV(1);
//		}

//		_delay_ms(100);
//		PORTE |= _BV(1);				// switch off the LED
//		PORTE = PORTE | (1 << 1);
//		PORTE = PORTE | 0b00000010;
//
//		_delay_ms(3500);
//		PORTE &= ~_BV(1);				// light it
//		PORTE = PORTE & ~(1 << 1);
//		PORTE = PORTE & ~0b00000010;
//		PORTE = PORTE & 0b11111101;

//void wait() {
//	uint32_t i;
//	for (i = 0; i < 16000000; i++) {
//	}
//}


//uint8_t* sendTelegram() {
//
//	uint8_t i;
//	// display telegram
////	for (i = 0; i < sizeof(myTelegram); i++) {
////		printf("%02x ", myTelegram[i]);
////	}
//
//	printf("sendTelegram(): sizeof(myTelegram): %d \n", sizeof(myTelegram));
//	// sendReadTelegram(myTelegram);
//
//	return myTelegram;
//}


// PATH: (i wystarczy.)
// c:\WINAVR\bin;c:\WINAVR\utils\bin;C:/eclipse/jre/bin/client;C:/eclipse/jre/bin;C:/eclipse/jre/lib/i386;c:\Windows\System32;c:\eclipse\cygwin\bin;c:\Program Files\Java\jre1.8.0_45\bin;C:\eclipse

// c:\PROGRA~2\Atmel\WinAVR-20100110\avr32;u:\lua\myEthernut330\include

// AVRDUDEPATH:
// c:\PROGRA~2\Atmel\AVRDUD~1.11-\bin

// log:
// U:\lua\myAVRLed2\Debug\myLED2.build.log

// include: (Linker -> Libraries path)
// c:\WINAVR\avr\include

// teraz komentasz z desktopa. popelnilem ribejs.

// ten ribejs jest dla remote tracking - origin/master  - komentasz od laptopa.

// no a jak cos napisze na desktopie. i zakomituje. i wypuszuje.
// a na laptopie skoleji nie zafeczuje. to bedzie rejektet.

// jak ribejs stanie, to prawym na skip.

//	uint16_t address;
//	uint16_t *myAddress;
//	address = 0x5555;
//	memPtr = &address;          // &address is the address of the location where 0x5555 is saved in memory
//								// it is in my case the 0x1077

	//	RS232_putstring("buffer: ");
	//	for (i = 0; i < 14; i++) {
	//		print_hexByte(myTelegram[i]);
	//		RS232_putstring(" ");
	//	}
	//	RS232_putstring("\r\n");

	//	unsigned char myChar = RS485_ReadChar();
	//	unsigned char myChar = RS232_ReadChar();
	//
	//	RS232_putstring("\r\nmyChar: ");
	//	print_hexByte(myChar);
	//	RS232_putstring("\r\n");

//	RS232_putstring("\r\nRS485_ReadChar_before \r\n");

//	for (i = 0; i < 4; i++) {
//		data = RS232_ReadChar();
//		{
//			if (data != 0x30) {
//				RS232_putstring("kucha! \r\n");
//			}
//			else {
//				RS232_putstring("brawo. dostalem 0. \r\n");
//			}
//		}
//	}


		// RS232_WriteChar(data);

//		data++;
//		if (data > 0x39) {
//			data = 0x30;
//		}

		// 0123456789abcd (14 signs)
		// 000102030405060708090a0b0c0d (28 signs)
// 		RS232_putstring(myString);
//		while (myDataPtr != 0x00) {
//			RS485_WriteChar(*myDataPtr);
//			myDataPtr++;
//		}

		// RS232_putstring(myData);

// char *myString = "000102030405060708090a0b0c0d\0\0";
	// char *myString = "000102030405060708090a0b0c0d";


//	uint8_t myData[32];
//	uint16_t *myDataPtr;
//	myDataPtr = &myData;
//
//	// clean the buffer
//	for (i = 0; i < 32; i++) {
//		myData[i] = 0x00 + i;
//	}
//
//	myData[0] = 0x31;
//	myData[1] = 0x32;
//	myData[2] = 0x33;
//	myData[3] = 0x34;
//	myData[4] = 0x35;
//	myData[5] = 0x36;
//
//	myData[26] = 0x30;
//	myData[27] = 0x30;
//	myData[28] = 0x00;
//	myData[29] = 0x00;
//	myData[30] = 0x00;
//	myData[31] = 0x00;
//
//	RS232_putstring("\r\n\r\n");
//	print_hexWord(myData);          // 10d7
//	RS232_putstring("\r\n");
//	print_hexWord(*myData);          // 0031
//	RS232_putstring("\r\n");
//	print_hexWord(myDataPtr);          // 10d7
//	RS232_putstring("\r\n");
//	print_hexWord(*myDataPtr);          // 3231
//	RS232_putstring("\r\n");
//	myDataPtr++;
//	print_hexWord(*myDataPtr);          // 3433
//	RS232_putstring("\r\n");
//	myDataPtr++;
//	print_hexWord(*myDataPtr);          // 3635
//	RS232_putstring("\r\n\r\n");
//
//	myDataPtr = &myData;
//	print_hexByte(myData);          // d7
//	RS232_putstring("\r\n");
//	print_hexByte(*myData);          // 31
//	RS232_putstring("\r\n");
//	print_hexByte(myDataPtr);          // d7
//	RS232_putstring("\r\n");
//	print_hexByte(*myDataPtr);          // 31
//	RS232_putstring("\r\n");
//	myDataPtr++;
//	print_hexByte(*myDataPtr);          // 33
//	RS232_putstring("\r\n");
//	myDataPtr++;
//	print_hexByte(*myDataPtr);          // 35
//	RS232_putstring("\r\n");
//	myDataPtr++;
//	print_hexByte(*myDataPtr);          // 06
//	RS232_putstring("\r\n\r\n\r\n");


	// read one parameter from MM
//	uint16_t myParam = 0x5e;
//	uint16_t value = getValue(myParam);
//	print_hexByte(myParam);
//	RS232_putstring(":");
//	print_hexWord(value);
//	RS232_putstring("\r\n");
//
//	getAllValues(mmParameters, mmParametersLength / 2);
//
//	for (i = 0; i < (mmParametersLength / 2); i++) {
//		print_hexWord(mmParametersCopy[i]);
//		RS232_putstring(": ");
//		print_hexWord(mmParameters[i]);
//		RS232_putstring("\r\n");
//	}

//////////////////////////////////

// telegram array for PPO1:
//unsigned char teleArr[11][14] = {
//		{ 0x02, 0x0C, 0x00, 0x07, 0xCE, 0x00, 0x00, 0x00, 0x00, 0x9F, 0x7F, 0x00, 0x00, 0x27 }, {
//				0x02, 0x0C, 0x00, 0x07, 0xCE, 0x00, 0x00, 0x00, 0x00, 0x9F, 0x7F, 0x00, 0x00, 0x27 }, {
//				0x02, 0x0C, 0x00, 0x10, 0x33, 0x00, 0x00, 0x00, 0x01, 0x0B, 0x7A, 0x00, 0x00, 0x5D }, {
//				0x02, 0x0C, 0x00, 0x10, 0x5B, 0x00, 0x00, 0x00, 0x00, 0x8C, 0x7E, 0x00, 0x00, 0xB7 }, {
//				0x02, 0x0C, 0x00, 0x10, 0x5C, 0x00, 0x00, 0x00, 0x04, 0x8C, 0x7E, 0x00, 0x00, 0xB4 }, {
//				0x02, 0x0C, 0x00, 0x10, 0x5D, 0x00, 0x00, 0x00, 0x2D, 0x0B, 0x72, 0x00, 0x00, 0x17 }, {
//				0x02, 0x0C, 0x00, 0x10, 0x5E, 0x00, 0x00, 0x13, 0x88, 0x0B, 0x72, 0x00, 0x00, 0xA2 }, {
//				0x02, 0x0C, 0x00, 0x10, 0x5F, 0x00, 0x00, 0x00, 0x01, 0x0B, 0x7A, 0x00, 0x00, 0x31 }, {
//				0x02, 0x0C, 0x00, 0x10, 0x5F, 0x00, 0x00, 0x00, 0x01, 0x0B, 0x72, 0x00, 0x00, 0x39 }, {
//				0x02, 0x0C, 0x00, 0x13, 0x8F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x92 }, {
//				0x02, 0x0C, 0x00, 0x13, 0x8E, 0x00, 0x00, 0x00, 0x04, 0x8C, 0x7E, 0x00, 0x00, 0x65 } };

// typedef unsigned char uint8_t;
//typedef uint8_t array_of_14_uint8_t[14];
//array_of_14_uint8_t *teleArrPtr = teleArr;

// typedef unsigned char uint8_t;		// 1 byte
// typedef unsigned short uint16_t;     // 2 bytes
// typedef unsigned int uint32_t;      // 4 bytes


//typedef unsigned int __attribute__((__mode__(QI))) uint8_t;
//typedef unsigned int __attribute__((__mode__(HI))) uint16_t;
//typedef unsigned int __attribute__((__mode__(SI))) uint32_t;
//typedef unsigned long long __attribute__((__mode__(DI))) uint64_t;
