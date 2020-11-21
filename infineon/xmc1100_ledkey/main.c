// http://www.microcontroller.it/Tutorials/Elettronica/componenti/tm1638.htm
// https://github.com/rjbatista/tm1638-library/blob/master/TM16XX.cpp
// https://github.com/MartyMacGyver/TM1638-demos-and-examples/blob/master/README.md

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include "tm1638.h"
#include "MyUtils.h"

void myCase1();
void myCase2();
void myCase3();
void myCase4();

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

	// str. 253 akapit 12.9.5 RCU Registers (SCU) w XMC1100_AA-Step_v11.pdf
	unsigned int reset_status;
	reset_status = SCU_RESET->RSTSTAT & 0x000003FF; /* get the cause of reset */
	SCU_RESET->RSTCLR = 1U; /* clear status field */
	SEGGER_RTT_printf(0, "reset_status: %d \r\n", reset_status);

	myInitLEDKey();

	//myCase1();
	//myCase2();
	//myCase3();
	myCase4();

}

void myCase1() {
	while (1U) {
		DIGITAL_IO_ToggleOutput(&LED0);

		for (int i = 14; i >= 0; i -= 2) {
			sendData(i, (0xff));
			sendData(i + 1, (0x07));
		}

		myDelayMS(1400);
		clearDisplay();
		myDelayMS(400);

		for (int i = 14; i >= 0; i -= 2) {
			sendData(i, (0xff));
			sendData(i + 1, (0x03));
		}

		myDelayMS(1400);
		clearDisplay();
		myDelayMS(400);

		for (int i = 14; i >= 0; i -= 2) {
			sendData(i, (0xff));
			sendData(i + 1, (0x01));
		}

		myDelayMS(1400);
		clearDisplay();
		myDelayMS(400);

		// wlacza fszyskie ledy
		for (int i = 14; i >= 0; i -= 2) {
			sendData(i, (0xff));
			sendData(i + 1, (0x00));
		}

		myDelayMS(1400);
		clearDisplay();
		myDelayMS(400);

		// wlacza fszyskie ledy
		for (int i = 14; i >= 0; i -= 2) {
			sendData(i, (0x7f));
			sendData(i + 1, (0x00));
		}

		//SEGGER_RTT_printf(0, "intensity: %d \r\n", intensity);
		//		for (i = 0; i <= max_intensity; i++) {
		//			sendCommand(0x80 | i | (1 << 3));
		//			myDelayMS(50);
		//		}
		//
		//		for (i = max_intensity; i >= 0; i--) {
		//			sendCommand(0x80 | i | (1 << 3));
		//			myDelayMS(50);
		//		}

		// a tu wygasza
		myDelayMS(1400);
		clearDisplay();
		myDelayMS(400);

		for (int i = 14; i >= 0; i -= 2) {
			sendData(i, (0x3f));
			sendData(i + 1, (0x00));
		}

		myDelayMS(1400);
		clearDisplay();
		myDelayMS(400);

		for (int i = 14; i >= 0; i -= 2) {
			sendData(i, (0x1f));
			sendData(i + 1, (0x00));
		}

		myDelayMS(1400);
		clearDisplay();
		myDelayMS(400);

		for (int i = 14; i >= 0; i -= 2) {
			sendData(i, (0x0f));
			sendData(i + 1, (0x00));
		}

		myDelayMS(1400);
		clearDisplay();
		myDelayMS(400);

		for (int i = 14; i >= 0; i -= 2) {
			sendData(i, (0x07));
			sendData(i + 1, (0x00));
		}

		myDelayMS(1400);
		clearDisplay();
		myDelayMS(400);

		for (int i = 14; i >= 0; i -= 2) {
			sendData(i, (0x03));
			sendData(i + 1, (0x00));
		}

		myDelayMS(1400);
		clearDisplay();
		myDelayMS(400);

		for (int i = 14; i >= 0; i -= 2) {
			sendData(i, (0x01));
			sendData(i + 1, (0x00));
		}

		myDelayMS(1400);
		clearDisplay();
		myDelayMS(400);

		for (int i = 14; i >= 0; i -= 2) {
			sendData(i, (0x00));
			sendData(i + 1, (0x00));
		}

		myDelayMS(1400);
		clearDisplay();
		myDelayMS(400);

		DIGITAL_IO_ToggleOutput(&LED0);

		//SEGGER_RTT_printf(0, "%02x \r\n", i);
	}
}

// scrolluje wszystkie znaki
void myCase2() {
	while (1U) {
		for (int i = 0; i < 94; i++) {
			DIGITAL_IO_ToggleOutput(&LED0);
			printChar(i);
			myDelayMS(400);
			clearDisplay();
		}
	}
}

void myCase3() {
	while (1U) {
		for (uint32_t i = 0; i < 16777216; i++) {
			DIGITAL_IO_ToggleOutput(&LED0);
			printNumber(i);
			//myDelayMS(100);
		}
	}
}

void myCase4() {
	while (1U) {
		for (uint16_t i = 9990, j = 10010; i < 10010; i++, j--) {
			DIGITAL_IO_ToggleOutput(&LED0);
			print1stNumber(i);
			print2ndNumber(j);
			myDelayMS(500);
			//SEGGER_RTT_printf(0, "%d : %d \r\n", i, j);
		}
	}
}

